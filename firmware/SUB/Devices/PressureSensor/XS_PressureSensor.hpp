/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef XS_PRESSURESENSOR_HPP
#define XS_PRESSURESENSOR_HPP

#include "PressureSensor/PressureSensorBase.hpp"
#include "Bus/RS485_Base.hpp"
#include "Verification/CRC.h"
#include <cstring>

template <uint8_t BusID>
class XS_PressureSensor : public PressureSensorBase {
public:
    explicit XS_PressureSensor(uint8_t addr_) : addr(addr_), agent(addr_, [this](uint8_t *data, size_t size) { Decode(data, size); }) {
        this->SetDivisionFactor(20);
        id = size;
        size++;
    }

    void Handle() override {
        static uint8_t cnt = 0;
        cnt++;
        if(id == index) {
            RequestPressure();
        }
        if(cnt >= size) {
            cnt = 0;
            index = (index + 1) % size;
        }

        // 计算采样频率
        if(HAL_GetTick() - lastTick >= 1000) {
            frequency = frequencyCounter;
            frequencyCounter = 0;
            lastTick = HAL_GetTick();
        }
    }

    static size_t GetInstanceNum() {
        return size;
    }

private:
    const uint8_t addr;
    uint8_t id;
    uint32_t lastTick = HAL_GetTick();
    float frequencyCounter{};
    RS485_Agent<BusID> agent;
    uint8_t txbuf[8]{};

    static size_t index;
    static size_t size;

    void RequestPressure() {
        txbuf[0] = addr; // 从机地址
        txbuf[1] = 0x03; // 功能码：读保持寄存器
        txbuf[2] = 0x00; // 起始地址高
        txbuf[3] = 0x16; // 起始地址低 (0x0016)
        txbuf[4] = 0x00; // 读取寄存器个数高
        txbuf[5] = 0x02; // 读取寄存器个数低 (0x0002)
        const uint16_t crc = CRC16Calc(txbuf, 6);
        txbuf[6] = crc & 0xFF;
        txbuf[7] = crc >> 8u;
        agent.Transmit(txbuf, 8);
    }

    void Decode(uint8_t *data, size_t size) {
        if (size != 9 || data[1] != 0x03 || data[2] != 4) {
            return;
        }

        const uint16_t receivedCrc = data[size - 2] | data[size - 1] << 8u;
        if (CRC16Calc(data, size - 2) != receivedCrc) {
            return;
        }

        uint32_t raw = (static_cast<uint32_t>(data[3]) << 24u) | (static_cast<uint32_t>(data[4]) << 16u) | (static_cast<uint32_t>(data[5]) << 8u) |
            static_cast<uint32_t>(data[6]);
        std::memcpy(&pressure, &raw, sizeof(float));

        frequencyCounter++;
    }
};

template <uint8_t BusID>
size_t XS_PressureSensor<BusID>::index = 0;

template <uint8_t BusID>
size_t XS_PressureSensor<BusID>::size = 0;

#endif //XS_PRESSURESENSOR_HPP
