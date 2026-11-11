/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef STREAMER_HPP
#define STREAMER_HPP

#include <cstring>

#include "ProjectConfig.h"
#include "Clamp.hpp"
#include "Verification/CRC.h"

class Streamer {
public:
    uint16_t bufferLength{};
    uint32_t poseSequence = 0;
    struct __attribute__((packed)) JoystickData {
        float yawRate;           // 偏航角角速度,逆时针为正
        float forwardSpeed;      // 前后速度，前进为正
        float leftRightSpeed;   // 左右速度，左移为正
        float downSpeed;         // 下降速度（归一化 0-1）
        float upSpeed;           // 上升速度（归一化 0-1）
        uint8_t startButton;     // 启动键
        uint8_t resetIO;
        uint8_t enablePathTracking;
        int8_t camYaw;
        int8_t camPitch;
        float globalX;           // 全局 X，单位 m，X 前为正
        float globalY;           // 全局 Y，单位 m，Y 左为正
        float globalYaw;         // 全局航向，单位 rad，逆时针为正
        float globalXVelocity;   // 全局 X 速度，单位 m/s
        float globalYVelocity;   // 全局 Y 速度，单位 m/s
        float globalYawRate;     // 全局偏航角速度，单位 rad/s，逆时针为正
    } joystickData;

    void Decode(uint8_t* data, uint16_t length) {
        ++poseSequence;
        bufferLength = length;

        // 帧头(1) + payload(49) + CRC(2) = 52 字节
        if (length != 52) {
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
            Clamp(joystickData.yawRate,-1.f,1.f);
            Clamp(joystickData.forwardSpeed,-1.f,1.f);
            Clamp(joystickData.leftRightSpeed,-1.f,1.f);
            poseValid = true;
            poseLastUpdateTick = HAL_GetTick();
        }
    }

    bool IsPoseFresh(uint32_t nowTick, uint32_t maxAgeMs) const {
        return poseValid && static_cast<uint32_t>(nowTick - poseLastUpdateTick) <= maxAgeMs;
    }

private:
    uint16_t calculated_crc {};
    uint16_t received_crc {};
    bool poseValid = false;
    uint32_t poseLastUpdateTick = 0;
};


#endif //STREAMER_HPP
