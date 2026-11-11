#ifndef FINEMOTE_DSHOT_H
#define FINEMOTE_DSHOT_H

#define DSHOT_MIN_THROTTLE              (48)
#define DSHOT_MAX_THROTTLE              (2047)
#define DSHOT_3D_FORWARD_MIN_THROTTLE   (1048)
#define DSHOT_3D_BACKWARD_MAX_THROTTLE  (1047)
#define DSHOT_RANGE                     (1999)
#define DSHOT_PACK_HEAD_LENGTH (2)
#define DSHOT_PACK_TAIL_LENGTH (2)
#define DSHOT_FRAME_LENGTH (16)
#define DSHOT_PACK_LENGTH (DSHOT_FRAME_LENGTH + DSHOT_PACK_HEAD_LENGTH + DSHOT_PACK_TAIL_LENGTH)
#define DSHOT_RX_LENGTH (100)
#define MOTOR_POLE_PAIR  8 // 大洋科技P75电机极对数


#include "BSP_DSHOT.h"
#include "DeviceBase.h"
#include "etl/map.h"
#include "etl/vector.h"
#include "arm_math.h"


class DSHOT_Port : public DeviceBase {
private:
    struct DSHOT_GPIO_PortPins {
        GPIO_TypeDef *port;
        etl::map<uint16_t, uint16_t, 16> pins; // 使用map存储每个引脚的DshotPack
        DSHOT_GPIO_PortPins(GPIO_TypeDef *_port, uint16_t ID) : port(_port) {
            pins[ID] = 0;
        }
    };
    etl::vector<DSHOT_GPIO_PortPins, 4> gpioPortsQueue = {};
    float RPMs[DSHOT_PIN_NUMBER + 1]{};
    uint16_t rxBuffer[DSHOT_RX_LENGTH] {};
    uint32_t outPutData[DSHOT_PACK_LENGTH * 3] {};
    uint16_t currentIndex = 0;
    bool isInverted = true; // 是否反相传输，开启时启动接收与解码功能

    // ── 卡尔曼滤波 (1D, 恒定状态 + 随机游走) ──
    // 状态方程: x_k = x_{k-1} + w_k,  w_k ~ N(0,Q)
    // 观测方程: z_k = x_k   + v_k,  v_k ~ N(0,R)
    float kfX[DSHOT_PIN_NUMBER + 1]{};   // 状态估计 (RPM)
    float kfP[DSHOT_PIN_NUMBER + 1]{};   // 误差协方差
    float kfQ = 50.0f;                    // 过程噪声 (RPM²), 越小越平滑, 默认 sqrt(50)≈7RPM/update
    float kfR = 10000.0f;                 // 观测噪声 (RPM²), 越小越信任测量, 默认 sqrt(10000)=100RPM

    // ── 3D 模式方向感知 ──
    bool  pin3DMode[DSHOT_PIN_NUMBER + 1]{};       // 每 pin 的 3D 模式标志

    DSHOT_Port(){}

    void UpdateMiddleBit(etl::map<uint16_t, uint16_t, 16> &pins)
    {
        for (int symbol_index = DSHOT_PACK_HEAD_LENGTH; symbol_index < DSHOT_FRAME_LENGTH + DSHOT_PACK_HEAD_LENGTH; symbol_index++) {
            outPutData[symbol_index * 3 + 1] = 0;          // Reset bits
        }
        for(auto &pin : pins) {
            uint16_t value = pin.second;
            uint16_t gpioPinMusk = BSP_DHOSTPinList[pin.first];
            uint32_t middleBitHigh = isInverted ? gpioPinMusk << 16 : gpioPinMusk;
            uint32_t middleBitLow = isInverted ? gpioPinMusk : gpioPinMusk << 16;
            for (int pos = DSHOT_PACK_HEAD_LENGTH; pos < DSHOT_FRAME_LENGTH + DSHOT_PACK_HEAD_LENGTH; pos++) {
                if (value & 0x8000) {
                    outPutData[pos * 3 + 1] |= middleBitHigh;
                }else {
                    outPutData[pos * 3 + 1] |= middleBitLow;
                }
                value <<= 1;
            }
        }
    }

    void GenerateMessage(etl::map<uint16_t, uint16_t, 16> &pins)
    {
        uint32_t portMask = 0;
        for(auto &pin : pins) {
            portMask |= BSP_DHOSTPinList[pin.first];
        }
        uint32_t resetMask;
        uint32_t setMask;

        if (isInverted) {
            resetMask = portMask;
            setMask = (portMask << 16);
        } else {
            resetMask = (portMask << 16);
            setMask = portMask;
        }

        for(int hold_bit_index = 0; hold_bit_index < DSHOT_PACK_HEAD_LENGTH; hold_bit_index++) {
            outPutData[hold_bit_index * 3 + 0] = resetMask; // Always reset all ports
            outPutData[hold_bit_index * 3 + 1] = resetMask;
            outPutData[hold_bit_index * 3 + 2] = resetMask;
        }
        for (int symbol_index = DSHOT_PACK_HEAD_LENGTH; symbol_index < DSHOT_FRAME_LENGTH + DSHOT_PACK_HEAD_LENGTH; symbol_index++) {
            outPutData[symbol_index * 3 + 0] = setMask ; // Always set all ports
            outPutData[symbol_index * 3 + 1] = 0;          // Reset bits are port dependent
            outPutData[symbol_index * 3 + 2] = resetMask; // Always reset all ports
        }
        for(int hold_bit_index = DSHOT_FRAME_LENGTH + DSHOT_PACK_HEAD_LENGTH; hold_bit_index < DSHOT_PACK_LENGTH; hold_bit_index++) {
            outPutData[hold_bit_index * 3 + 0] = resetMask; // Always reset all ports
            outPutData[hold_bit_index * 3 + 1] = resetMask;
            outPutData[hold_bit_index * 3 + 2] = resetMask;
        }

        UpdateMiddleBit(pins);
    }

    /*** 以下为双向DSHOT遥测接收与解码函数 (基于Betaflight decode_bb) ***/

    // ── 常量 (与Betaflight dshot_bitbang_decode.c 一致) ──
    #define MIN_VALID_BBSAMPLES 57   // (21-2)*3
    #define MAX_VALID_BBSAMPLES 69   // (21+2)*3
    #define DSHOT_TELEMETRY_NOEDGE  0xFFFE
    #define DSHOT_TELEMETRY_INVALID 0xFFFF
    #define ERPM_PER_LSB            100.0f


    /*
     * 步骤1: GCR 5→4 查表解码 + CRC 校验 (Betaflight decode_bb_value)
     * 输入: 21-bit GCR 码流 (含 1-bit 起始位 + 4×5-bit GCR 组)
     * 输出: 12-bit 原始遥测数据, 或 DSHOT_TELEMETRY_INVALID
     */
    static uint32_t decode_bb_value(uint32_t value) {
        value &= 0xFFFFF;  // 丢弃起始位, 保留低 20 位

        // GCR(5,4) 查表: 5-bit GCR 码字 → 4-bit 数据 nibble
        static const uint32_t gcr_decode[32] = {
            0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
            0xFFFFFFFF, 9,          10,         11,          0xFFFFFFFF, 13,         14,         15,
            0xFFFFFFFF, 0xFFFFFFFF, 2,          3,           0xFFFFFFFF, 5,          6,          7,
            0xFFFFFFFF, 0,          8,          1,           0xFFFFFFFF, 4,          12,         0xFFFFFFFF
        };

        uint32_t decodedValue  = gcr_decode[ value        & 0x1F];
        decodedValue          |= gcr_decode[(value >>  5) & 0x1F] << 4;
        decodedValue          |= gcr_decode[(value >> 10) & 0x1F] << 8;
        decodedValue          |= gcr_decode[(value >> 15) & 0x1F] << 12;

        // CRC 校验: XOR bytes → XOR nibbles → 必须等于 0xF
        uint32_t csum = decodedValue;
        csum = csum ^ (csum >> 8);
        csum = csum ^ (csum >> 4);

        if ((csum & 0xF) != 0xF || decodedValue > 0xFFFF) {
            return DSHOT_TELEMETRY_INVALID;
        }
        return decodedValue >> 4;  // 去掉 CRC, 返回 12-bit rawValue
    }


    /*
     * 步骤2: 边沿检测 → GCR 码流重建 (Betaflight decode_bb 算法, 4路展开优化)
     *
     * 直接操作 DMA 原始 uint16_t buffer + pinMask, 消除中间复制.
     * 4路展开: 每次循环检查 4 个采样点, 降低 75% 循环开销.
     *
     * 帧结构: [1-bit start] + 4×[5-bit GCR] = 21 bits
     */
    static uint32_t decode_bb_telemetry(const uint16_t* buffer, size_t count, uint16_t pinMask) {
        uint32_t value = 0;
        size_t idx = 0;

        // ── 阶段A: 4路展开跳过前导高电平, 找第一个下降沿 ──
        while (idx + 4 <= count) {
            if (!(buffer[idx] & pinMask) || !(buffer[idx+1] & pinMask) ||
                !(buffer[idx+2] & pinMask) || !(buffer[idx+3] & pinMask)) {
                break;
            }
            idx += 4;
        }
        // 逐采样定位到精确的第一个 LOW
        while (idx < count && (buffer[idx] & pinMask)) {
            idx++;
        }
        if (idx >= count - MIN_VALID_BBSAMPLES) {
            return DSHOT_TELEMETRY_NOEDGE;
        }

        // ── 阶段B: 4路展开边沿检测主循环 ──
        size_t remaining = (count - idx) < MAX_VALID_BBSAMPLES
                           ? (count - idx) : MAX_VALID_BBSAMPLES;
        size_t endIdx      = idx + remaining;
        size_t oldIdx      = idx;
        uint16_t lastValue = 0;   // 当前所在电平 (0=LOW, pinMask=HIGH)
        uint32_t bits      = 0;

        while (idx < endIdx) {
            // 4路展开扫描电平变化 (边沿)
            while (idx + 4 <= endIdx) {
                if ((buffer[idx] & pinMask) != lastValue ||
                    (buffer[idx+1] & pinMask) != lastValue ||
                    (buffer[idx+2] & pinMask) != lastValue ||
                    (buffer[idx+3] & pinMask) != lastValue) {
                    break;
                }
                idx += 4;
            }
            // 逐采样定位到精确边沿
            while (idx < endIdx && (buffer[idx] & pinMask) == lastValue) {
                idx++;
            }
            if (idx >= endIdx) break;

            // 边沿找到: len = (采样点数 + 1) / 3, 最少为 1
            uint32_t sampleCount = idx - oldIdx;
            uint32_t len = (sampleCount + 1) / 3;
            if (len < 1) len = 1;

            bits += len;
            value <<= len;
            value |= 1UL << (len - 1);

            oldIdx = idx;
            lastValue = (buffer[idx] & pinMask);
        }

        // ── 阶段C: 最后一个符号推断 ──
        if (bits < 18) {
            return DSHOT_TELEMETRY_NOEDGE;
        }
        int nlen = 21 - (int)bits;
        if (nlen < 0) {
            return DSHOT_TELEMETRY_NOEDGE;
        }
        if (nlen > 0) {
            value <<= nlen;
            value |= 1UL << (nlen - 1);
        }

        return decode_bb_value(value);
    }


    /*
     * 步骤3: eRPM 遥测值解码 (Betaflight dshot_decode_eRPM_telemetry_value)
     *
     * 12-bit rawValue 格式: eeem mmmm mmmm
     *   高3位指数(e) + 低9位尾数(m) → 周期 = mantissa << exponent
     * 返回: eRPM * 100
     */
    static uint32_t dshot_decode_eRPM_telemetry_value(uint16_t rawValue) {
        if (rawValue == 0x0FFF) {
            return 0;  // 电机停转
        }
        uint32_t period = (rawValue & 0x01FF) << ((rawValue & 0xFE00) >> 9);
        if (period == 0) {
            return DSHOT_TELEMETRY_INVALID;
        }
        // eRPM*100 = (1000000*60/100 + period/2) / period
        return (1000000UL * 60 / 100 + period / 2) / period;
    }


    /*
     * 步骤4: eRPM → 机械转速 RPM (Betaflight erpmToRpm)
     *   rpm = eRPM100 * ERPM_PER_LSB / MOTOR_POLE_PAIR
     *       = eRPM100 * 100 / 极对数
     */
    static float erpmToRpm(uint32_t eRPM100) {
        return eRPM100 * ERPM_PER_LSB / static_cast<float>(MOTOR_POLE_PAIR);
    }


    /*
     * 步骤5: 完整解码流水线 (直接操作 DMA raw buffer, 无中间复制)
     *   decode_bb_telemetry → decode_bb_value →
     *   dshot_decode_eRPM_telemetry_value → erpmToRpm
     * buffer: DMA 采样的 uint16_t GPIO 端口快照
     * pinMask: 目标 pin 的位掩码
     * 返回: 机械转速 RPM, 0=停转, 负值=失败
     */
    float CalaVelForBuffer(const uint16_t* buffer, size_t len, uint16_t pinMask) {
        uint32_t rawValue = decode_bb_telemetry(buffer, len, pinMask);
        if (rawValue == DSHOT_TELEMETRY_NOEDGE || rawValue == DSHOT_TELEMETRY_INVALID) {
            return -1.0f;
        }
        uint32_t eRPM100 = dshot_decode_eRPM_telemetry_value((uint16_t)rawValue);
        if (eRPM100 == DSHOT_TELEMETRY_INVALID) {
            return -1.0f;
        }
        if (eRPM100 == 0) {
            return 0.0f;  // 电机停转
        }
        return erpmToRpm(eRPM100);
    }


    /*
     * 步骤6: 从 DMA 采样 buffer 中解码各 pin 转速 (零拷贝, 直接操作 raw buffer)
     * rxBuffer[] 是 DMA 采样的 GPIOx->IDR 快照 (uint16_t)
     *
     * 解码后处理:
     *   ① 3D 模式下根据油门方向给转速加正负号
     *   ② 卡尔曼滤波
     *   ③ 存储最终结果到 RPMs[]
     */
    void DecodeReceivedPort(size_t portQueueIndex) {
        if (portQueueIndex >= gpioPortsQueue.size()) return;
        DSHOT_GPIO_PortPins &entry = gpioPortsQueue[portQueueIndex];

        for (auto &pin : entry.pins) {
            uint16_t pinMask = BSP_DHOSTPinList[pin.first];
            float rpm = CalaVelForBuffer(rxBuffer, DSHOT_RX_LENGTH, pinMask);
            uint8_t id = pin.first;
            if (rpm >= 0.0f) {
                // ── ① 3D 模式方向符号 ──
                if (pin3DMode[id]) {
                    uint16_t dshotPack = pin.second;          // 当前 DSHOT 数据包
                    uint16_t throttle  = dshotPack >> 5;      // 提取油门值 [10:0]
                    if (throttle > 0 && throttle < DSHOT_3D_FORWARD_MIN_THROTTLE) {
                        rpm = -rpm;  // 反转: 油门 48~1047
                    }
                }
                // ── ② 卡尔曼滤波 ──
                // Predict: 状态不变, 协方差增长 (随机游走)
                float p = kfP[id] + kfQ;
                // Update
                float k = p / (p + kfR);          // 卡尔曼增益
                kfX[id] += k * (rpm - kfX[id]);    // 状态更新
                kfP[id] = (1.0f - k) * p;          // 协方差更新
                RPMs[id] = kfX[id];
            }
        }
    }

    /*** 接收与解码函数END ***/


public:
    DSHOT_Port(const DSHOT_Port&) = delete;
    DSHOT_Port& operator=(const DSHOT_Port&) = delete;

    static DSHOT_Port& GetInstance() {
        static DSHOT_Port instance;
        return instance;
    }

    void AddPin(GPIO_TypeDef *port, uint16_t ID) {
        for(auto &data : gpioPortsQueue) {
            if(data.port == port) {
                data.pins[ID] = 0;
                return;
            }
        }
        if(!gpioPortsQueue.full()) {
            gpioPortsQueue.push_back(DSHOT_GPIO_PortPins(port, ID));
        }
        else {
            // 如果队列已满，可以选择覆盖最旧的元素或抛出异常
            gpioPortsQueue[0] = DSHOT_GPIO_PortPins(port, ID);
        }
    }

    void SetDataPack(GPIO_TypeDef *port, uint16_t ID, uint16_t DshotDataPack) {
        for(auto &data : gpioPortsQueue) {
            if(data.port == port && data.pins.count(ID)) {
                data.pins[ID] = DshotDataPack;
                return;
            }
        }
    }

    bool InvertState() const{
        return isInverted;
    }

    void TransmitMessage() {
        if (currentIndex >= gpioPortsQueue.size()) {
            return; // 队列已遍历完毕
        }

        if(isInverted) {
            uint16_t pinMusk = 0;
            for(auto &pin : gpioPortsQueue[currentIndex].pins) {
                pinMusk |= BSP_DHOSTPinList[pin.first];
            }
            BSP_DSHOTs::GetInstance().SetPinsOutput(gpioPortsQueue[currentIndex].port, pinMusk);
        }

        GenerateMessage(gpioPortsQueue[currentIndex].pins);
        BSP_DSHOTs::GetInstance().TransmitMessage(outPutData, gpioPortsQueue[currentIndex].port, DSHOT_PACK_LENGTH * 3);
        currentIndex++;
    }

    void ReceiveMessage() {
        uint16_t pinMusk = 0;
        for(auto &pin : gpioPortsQueue[currentIndex-1].pins) {
            pinMusk |= BSP_DHOSTPinList[pin.first];
        }
        BSP_DSHOTs::GetInstance().SetPinsInput(gpioPortsQueue[currentIndex-1].port, pinMusk);
        BSP_DSHOTs::GetInstance().RecceiveMessage((uint32_t*)rxBuffer, gpioPortsQueue[currentIndex-1].port, DSHOT_RX_LENGTH);
    }

    /*** new add ***/
    void Deccode() {
        DecodeReceivedPort(currentIndex-1);
    }

    float getRPM(uint16_t ID) {
        if(ID == 0 || ID > DSHOT_PIN_NUMBER) {
            return -1.0f; // 无效ID
        }
        return RPMs[ID];
    }

    // ── 卡尔曼滤波器配置 ──
    //
    // Q (过程噪声): RPM 在一帧内可能变化的方差
    //   大 → 跟踪快但噪声多, 小 → 平滑但滞后
    //   典型: 10~500, 默认 50 (std≈7 RPM/update)
    //
    // R (观测噪声): DSHOT 遥测的测量方差
    //   大 → 更不信任测量 (更平滑), 小 → 更信任测量
    //   典型: 1000~50000, 默认 10000 (std≈100 RPM)
    //
    // 稳态增益: k_ss ≈ sqrt(Q/R)
    //   默认 sqrt(50/10000) ≈ 0.071 (约 14 帧到 63%)

    void SetKalmanQ(float q) { if (q > 0.0f) kfQ = q; }
    void SetKalmanR(float r) { if (r > 0.0f) kfR = r; }

    // 便捷: 设置 Q 和 R 并重置滤波器状态
    void SetKalmanFilter(float Q, float R) {
        kfQ = Q; kfR = R;
        for (size_t i = 0; i <= DSHOT_PIN_NUMBER; i++) {
            kfX[i] = 0.0f;
            kfP[i] = R;  // 初始协方差 = R, 首帧测量获得 ~0.5 的权重
        }
    }

    // 设置单个 pin 的 3D 模式
    void SetPin3DMode(uint16_t ID, bool enable) {
        if (ID > 0 && ID <= DSHOT_PIN_NUMBER) {
            pin3DMode[ID] = enable;
        }
    }

    // 获取卡尔曼状态 (调试用)
    float getKalmanState(uint16_t ID) {
        if (ID == 0 || ID > DSHOT_PIN_NUMBER) return -1.0f;
        return kfX[ID];
    }
    float getKalmanGain(uint16_t ID) {
        if (ID == 0 || ID > DSHOT_PIN_NUMBER) return -1.0f;
        float p = kfP[ID] + kfQ;
        return p / (p + kfR);
    }
    /*** end ***/

    void Handle() override {
        currentIndex = 0; // 每次处理时从头开始
        TransmitMessage();
    }
};



template <uint16_t ID>
class DSHOT_PIN {
public:
    DSHOT_PIN(const DSHOT_PIN &) = delete;
    DSHOT_PIN &operator=(const DSHOT_PIN &) = delete;
    static DSHOT_PIN &GetInstance() {
        static DSHOT_PIN instance;
        return instance;
    }

    float GetRPM() {
        return DSHOT_Port::GetInstance().getRPM(ID);
    }

    void SetIntThrottle(int integerThrottle) {
        if(!isMotorEnabled) {
            targetThrottle = 0;
            GenerateDshotPack();
            return;
        }

        targetThrottle = integerThrottle;
        GenerateDshotPack();
    }

    void SetTargetThrottle(float throttle) {
        if(!isMotorEnabled) {
            targetThrottle = 0;
            GenerateDshotPack();
            return;
        }
        // range of throttle 3D(-1，1), normal(0，1)
        if(is3DModeEnabled) {
            if (fabsf(throttle) < 1e-6f) {
                targetThrottle = 0;
            }
            else {
                if(throttle < 0) {
                    targetThrottle = DSHOT_MIN_THROTTLE + static_cast<int>(roundf(fabsf(throttle) * (DSHOT_3D_BACKWARD_MAX_THROTTLE - DSHOT_MIN_THROTTLE)));
                    targetThrottle = targetThrottle < DSHOT_MIN_THROTTLE ? DSHOT_MIN_THROTTLE : targetThrottle;
                    targetThrottle = targetThrottle > DSHOT_3D_BACKWARD_MAX_THROTTLE ? DSHOT_3D_BACKWARD_MAX_THROTTLE : targetThrottle;
                }
                else {
                    targetThrottle = DSHOT_3D_FORWARD_MIN_THROTTLE + static_cast<int>(roundf(throttle * (DSHOT_MAX_THROTTLE - DSHOT_3D_FORWARD_MIN_THROTTLE)));
                    targetThrottle = targetThrottle < DSHOT_3D_FORWARD_MIN_THROTTLE ? DSHOT_3D_FORWARD_MIN_THROTTLE : targetThrottle;
                    targetThrottle = targetThrottle > DSHOT_MAX_THROTTLE ? DSHOT_MAX_THROTTLE : targetThrottle;
                }
            }
        }
        else {
            int integerThrottle = static_cast<int>(roundf(throttle * DSHOT_RANGE));
            targetThrottle = integerThrottle > DSHOT_RANGE ? DSHOT_MAX_THROTTLE : (integerThrottle <= 0 ? 0 : integerThrottle + DSHOT_MIN_THROTTLE); // 1-47保留为特殊指令
        }

        GenerateDshotPack();
    }

    void Set3DMode(bool isEnable) {
        is3DModeEnabled = isEnable;
        DSHOT_Port::GetInstance().SetPin3DMode(ID, isEnable);
    }

    void SetTelemetry(bool isEnable) {
        telemetryRequest = isEnable;
    }

    void EnableMotor() {
        isMotorEnabled = true;
    }

    void DisableMotor() {
        isMotorEnabled = false;
        targetThrottle = 0;
        GenerateDshotPack();
    }

private:
    uint16_t targetThrottle = 0;
    bool is3DModeEnabled = true;
    bool isInverted; // 这里的isInverted会被DSHOT_PORT初始化
    bool telemetryRequest = true;
    bool isMotorEnabled = false; // 是否允许电机工作

    DSHOT_PIN() {
        BSP_DSHOT<ID>::GetInstance();
        DSHOT_Port::GetInstance().AddPin(BSP_DHOSTPortList[ID], ID);
        isInverted = DSHOT_Port::GetInstance().InvertState();//同一个GPIO PORT下不同的PIN必须保持一致
    }

    void GenerateDshotPack() {
        // 构建完整DShot数据包（11位油门 + 1位遥测 + 4位CRC）
        uint16_t packet{0};
        packet |= (targetThrottle << 5);
        packet |= (telemetryRequest ? 1<<4 : 0<<4);

        // 计算CRC并合并到数据包
        uint8_t crc = (packet >> 4) ^ (packet >> 8) ^ (packet >> 12);  // 取前12位计算
        if(isInverted) {
            crc = ~crc;
        }
        packet |= crc & 0x0F;

        DSHOT_Port::GetInstance().SetDataPack(BSP_DHOSTPortList[ID], ID, packet);
    }
};

inline void DMA_XferCpltCallback(DMA_HandleTypeDef *hdma) {
    if (hdma->Instance == DSHOT_TRANSMIT_DMA_HANDLE.Instance) {
        if(DSHOT_Port::GetInstance().InvertState()) {
            DSHOT_Port::GetInstance().ReceiveMessage();
        }
        else {
            DSHOT_Port::GetInstance().TransmitMessage();
        }
    }
    else if (hdma->Instance == DSHOT_RECEIVE_DMA_HANDLE.Instance) {
        if(DSHOT_Port::GetInstance().InvertState()) {
            DSHOT_Port::GetInstance().Deccode();
            DSHOT_Port::GetInstance().TransmitMessage();
        }
    }
}

#endif
