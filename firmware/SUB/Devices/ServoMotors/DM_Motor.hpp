/*******************************************************************************
 * Copyright (c) 2026.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef FINEMOTE_DM_MOTOR_HPP
#define FINEMOTE_DM_MOTOR_HPP

#include <fast_math_functions.h>


#include "Bus/CAN_Base.hpp"
#include "ServoMotors/MotorBase.hpp"

template <int busID>
class DM_Motor : public MotorBase {
public:
    template <typename T>
    DM_Motor(const Motor_Param_t &&params, T &_controller, float _mitMaxPosition, float _mitMaxSpeed, float _mitMaxTorque, uint32_t addr) :
        MotorBase(std::forward<const Motor_Param_t>(params)), mitModeParam({_mitMaxPosition,_mitMaxSpeed,_mitMaxTorque,0,0,0,0,0}),canAgent(addr) {
        ResetController(_controller);
        initTick = HAL_GetTick();
    }

    void SetMitModeTarget(float position, float speed, float torque, float Kp, float Kd) {
        mitModeParam.position = position;
        mitModeParam.speed = speed;
        mitModeParam.torque = torque;
        mitModeParam.Kp = Kp;
        mitModeParam.Kd = Kd;
    }

    void Handle() final {
        Update();
        controller->Calc();
        if (HAL_GetTick() - initTick < 5000) {
            Enable();
        } else {
            MessageGenerate();
        }
    };

    CAN_Agent<busID> canAgent;

private:
    uint32_t initTick;

    struct MitModeParam {
        float maxPosition; //单位弧度
        float maxSpeed; //单位rad/s
        float maxTorque; //单位N*M
        float position; //期望位置
        float speed; //期望速度
        float torque; //转矩给定值
        float Kp; //位置比例系数
        float Kd; //位置微分系数
    } mitModeParam;

    void SetFeedback() final {
        switch (params.targetType) {
        case Motor_Ctrl_Type_e::Position:
            controller->SetFeedback({&state.position, &state.speed});
            break;
        case Motor_Ctrl_Type_e::Speed:
            controller->SetFeedback({&state.speed});
            break;
        }
    }

    void Enable() override{
        canAgent[0] = 0xFF;
        canAgent[1] = 0xFF;
        canAgent[2] = 0xFF;
        canAgent[3] = 0xFF;
        canAgent[4] = 0xFF;
        canAgent[5] = 0XFF;
        canAgent[6] = 0xFF;
        canAgent[7] = 0xFC;
        canAgent.Transmit(canAgent.addr);
    }

    void Disable() override {
        canAgent[0] = 0xFF;
        canAgent[1] = 0xFF;
        canAgent[2] = 0xFF;
        canAgent[3] = 0xFF;
        canAgent[4] = 0xFF;
        canAgent[5] = 0XFF;
        canAgent[6] = 0xFF;
        canAgent[7] = 0xFD;
        canAgent.Transmit(canAgent.addr);
    }

    uint16_t float_to_uint(float x, float x_min, float x_max, uint8_t bits) {
        float span = x_max - x_min;
        float offset = x_min;
        return static_cast<uint16_t>((x - offset) * static_cast<float>((1<<bits)-1)/span);
    }

    float uint_to_float(uint16_t x_int, float x_min, float x_max, uint8_t bits)
    {
        float span = x_max - x_min;
        float offset = x_min;
        return (static_cast<float>(x_int)) * span / (static_cast<float>((1 << bits) - 1)) + offset;
    }

    void MessageGenerate() {
        switch (params.ctrlType) {
        case  Motor_Ctrl_Type_e::Torque: //实际为MIT模式
            {
                uint16_t txPositionCode = float_to_uint(mitModeParam.position, -mitModeParam.maxPosition, mitModeParam.maxPosition, 16);
                uint16_t txSpeedCode = float_to_uint(mitModeParam.speed, -mitModeParam.maxSpeed, mitModeParam.maxSpeed, 12);
                uint16_t KpCode = float_to_uint(mitModeParam.Kp, 0, 500, 12);//KpMax默认500
                uint16_t KdCode = float_to_uint(mitModeParam.Kd, 0, 5, 12);//KdMax默认5
                uint16_t txTorqueCode = float_to_uint(mitModeParam.torque, -mitModeParam.maxTorque, mitModeParam.maxTorque, 12);

                canAgent[0] = txPositionCode >> 8;
                canAgent[1] = txPositionCode;
                canAgent[2] = txSpeedCode >> 4;
                canAgent[3] = (txSpeedCode & 0xF) << 4 | KpCode >> 8;
                canAgent[4] = KpCode;
                canAgent[5] = KdCode >> 4;
                canAgent[6] = (KdCode & 0xF) << 4 | txTorqueCode >> 8;
                canAgent[7] = txTorqueCode;
                canAgent.Transmit(canAgent.addr);
                break;
            }
        case Motor_Ctrl_Type_e::Position: //位置速度控制
            {
                float txPosition = controller->GetOutput() / 180.f * 3.14159265358979f;
                float txVelocity = 0.2f; // 单位rad/s
                uint32_t txPositionCode;
                uint32_t txVelocityCode;
                memcpy(&txPositionCode, &txPosition, sizeof(float));
                memcpy(&txVelocityCode, &txVelocity, sizeof(float));
                canAgent[0] = txPositionCode & 0xFF;
                canAgent[1] = txPositionCode >> 8 & 0xFF;
                canAgent[2] = txPositionCode >> 16 & 0xFF;
                canAgent[3] = txPositionCode >> 24 & 0xFF;
                canAgent[4] = txVelocityCode & 0xFF;
                canAgent[5] = txVelocityCode >> 8 & 0xFF;
                canAgent[6] = txVelocityCode >> 16 & 0xFF;
                canAgent[7] = txVelocityCode >> 24 & 0xFF;
                canAgent.Transmit(canAgent.addr + 0x100);
                break;
            }
        }
    }

    void Update() { // 正方向取CCW
        uint8_t id = (canAgent.rxbuf[0])&0x0F;
        if(canAgent.addr == id) {
            uint8_t motorState = (canAgent.rxbuf[0])>>4;
            uint16_t positionCode=(canAgent.rxbuf[1]<<8)|canAgent.rxbuf[2];
            uint16_t velocityCode=(canAgent.rxbuf[3]<<4)|(canAgent.rxbuf[4]>>4);
            uint16_t torqueCode=((canAgent.rxbuf[4]&0xF)<<8)|canAgent.rxbuf[5];
            state.position = uint_to_float(positionCode, -mitModeParam.maxPosition, mitModeParam.maxPosition, 16);
            state.speed = uint_to_float(velocityCode, -mitModeParam.maxSpeed, mitModeParam.maxSpeed, 12);
            state.torque = uint_to_float(torqueCode, -mitModeParam.maxTorque, mitModeParam.maxTorque, 12);
            float mosfetTemperature = static_cast<float>(canAgent.rxbuf[6]);//MOS管温度
            state.temperature = static_cast<float>(canAgent.rxbuf[7]);//线圈温度
        }
    }
};

#endif
