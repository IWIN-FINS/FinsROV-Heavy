/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef STREAMER_HPP
#define STREAMER_HPP

#include "ProjectConfig.h"

#include "Verification/CRC.h"

class Streamer {
public:
    struct JoystickData {
        float yawRate;           // 偏航角角速度,逆时针为正
        float forwardSpeed;      // 前后速度，前进为正
        float leftRightSpeed;   // 左右速度，左移为正
        float downSpeed;         // 下降速度（归一化 0-1）
        float upSpeed;           // 上升速度（归一化 0-1）
        uint8_t startButton;     // 启动键
        uint8_t camFillLight;
        uint8_t frameFillLight;
        int8_t camYaw;
        int8_t camPitch;
    } joystickData __packed;

    void Decode(uint8_t* data, uint16_t length) {
        // 检查最小长度：帧头(1) + 数据(25) + CRC(2) = 24字节
        if (length != 28) {
            return;
        }

        // 检查帧头
        if (data[0] != 0xAA) {
            return;
        }

        calculated_crc = CRC16Calc(data, length - 2);
        received_crc = data[length - 1] << 8u | data[length - 2];

        if (calculated_crc == received_crc) {
            std::memcpy(&joystickData, data + 1, sizeof(JoystickData));
        }
    }

private:
    uint16_t calculated_crc {};
    uint16_t received_crc {};
};


#endif //STREAMER_HPP
