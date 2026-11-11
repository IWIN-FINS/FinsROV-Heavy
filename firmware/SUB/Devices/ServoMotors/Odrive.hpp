/*******************************************************************************
* Copyright (c) 2024.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef FINEMOTE_ODRIVE_H
#define FINEMOTE_ODRIVE_H

#include "Bus/CAN_Base.hpp"
#include "ServoMotors/MotorBase.hpp"
#include "Clamp.hpp"

enum class OdriveAxisState {
    AXIS_STATE_UNDEFINED = 0,
    AXIS_STATE_IDLE = 1, //释放电机
    AXIS_STATE_STARTUP_SEQUENCE = 2,
    AXIS_STATE_FULL_CALIBRATION_SEQUENCE = 3, //完整参数校准
    AXIS_STATE_MOTOR_CALIBRATION = 4, //电机校准
    AXIS_STATE_ENCODER_INDEX_SEARCH = 6,
    AXIS_STATE_ENCODER_OFFSET_CALIBRATION = 7, //编码器校准
    AXIS_STATE_CLOSED_LOOP_CONTROL = 8, //闭环模式
    AXIS_STATE_LOCKIN_SPIN = 9,
    AXIS_STATE_ENCODER_DIR_FIND = 10,
    AXIS_STATE_MOTOR_CALIBRATION_FLUX = 11,
};

enum class OdriveControlMode {
    CONTROL_MODE_VOLTAG00E_CONTROL = 0,
    CONTROL_MODE_TORQUE_CONTROL = 1, //力矩控制
    CONTROL_MODE_VELOCITY_CONTROL = 2, //速度控制
    CONTROL_MODE_POSITION_CONTROL = 3, //位置控制
    };

enum class OdriveInputMode {
    INPUT_MODE_INACTIVE = 0,
    INPUT_MODE_PASSTHROUGH = 1,//直接输入
    INPUT_MODE_VEL_RAMP = 2, //速度斜率
    INPUT_MODE_POS_FILTER = 3,//位置滤波
    INPUT_MODE_TRAP_TRAJ = 5,//梯形位置
    INPUT_MODE_TORQUE_RAMP = 6,//力矩斜率
    INPUT_MODE_TUNING = 7,
};

enum class OdriveRebootMode{
    REBOOT = 0,
    SAVE_AND_REBOOT = 1,
};

template <int busID>
class Odrive : public MotorBase {
public:
    template<typename T>
    Odrive(const Motor_Param_t&& params, T& _controller, uint32_t addr) : MotorBase(std::forward<const Motor_Param_t>(params)), canAgent(addr) {
        ResetController(_controller);
        this->SetDivisionFactor(20);
    }

    void Enable() override {
        ClearErrors();
        SetAxisState(static_cast<uint32_t>(OdriveAxisState::AXIS_STATE_CLOSED_LOOP_CONTROL));
        // SetControllerMode(static_cast<uint32_t>(OdriveControlMode::CONTROL_MODE_POSITION_CONTROL), static_cast<uint32_t>(OdriveInputMode::INPUT_MODE_TRAP_TRAJ));
        SetControllerMode(static_cast<uint32_t>(OdriveControlMode::CONTROL_MODE_VELOCITY_CONTROL), static_cast<uint32_t>(OdriveInputMode::INPUT_MODE_PASSTHROUGH));
        isEnable = true;
    }

    void Disable() override {
        SetAxisState(static_cast<uint32_t>(OdriveAxisState::AXIS_STATE_IDLE));
        isEnable = false;
    }

    void EncoderCalibration() {
        SetAxisState(static_cast<uint32_t>(OdriveAxisState::AXIS_STATE_ENCODER_OFFSET_CALIBRATION));
    }

    void Reboot(uint32_t rebootMode) {
        for (int i = 0; i < 4; ++i) {
            canAgent[i] = (rebootMode >> (i * 8)) & 0xFF;
        }
        canAgent[4] = 0x00;
        canAgent[5] = 0x00;
        canAgent[6] = 0x00;
        canAgent[7] = 0x00;
        canAgent.Transmit(canAgent.addr << 5 | 0x16,CAN_ID_STD | CAN_RTR_DATA);
    }

    void SetPoseGain(float posGain) {
        uint32_t gain = static_cast<uint32_t>(posGain);
        for (int i = 0; i < 4; ++i) {
            canAgent[i] = (gain >> (i * 8)) & 0xFF;
        }
        canAgent[4] = 0x00;
        canAgent[5] = 0x00;
        canAgent[6] = 0x00;
        canAgent[7] = 0x00;
        canAgent.Transmit(canAgent.addr << 5 | 0x1a,CAN_ID_STD | CAN_RTR_DATA);
    }

    void Handle() final{
        if(isEnable) {
            Update();
            controller->Calc();
            MessageGenerate();
        }
    }

    CAN_Agent<busID> canAgent;

private:
    void SetFeedback() final{
        switch (params.targetType) {
            case Motor_Ctrl_Type_e::Position:
                controller->SetFeedback({&state.position, &state.speed});
                break;
            case Motor_Ctrl_Type_e::Speed:
                controller->SetFeedback({&state.speed});
                break;
        }
    }

    void SetAxisState(uint32_t axisState) {
        for (int i = 0; i < 4; ++i) {
            canAgent[i] = (axisState >> (i * 8)) & 0xFF;
        }
        canAgent[4] = 0x00;
        canAgent[5] = 0x00;
        canAgent[6] = 0x00;
        canAgent[7] = 0x00;
        canAgent.Transmit(canAgent.addr << 5 | 0x07,CAN_ID_STD | CAN_RTR_DATA);
    }

    void SetControllerMode(uint32_t ctrlMode, uint32_t inputMode) {
        for (int i = 0; i < 4; ++i) {
            canAgent[i] = (ctrlMode >> (i * 8)) & 0xFF;
        }
        for (int i = 0; i < 4; ++i) {
            canAgent[i + 4] = (inputMode >> (i * 8)) & 0xFF;
        }
        canAgent.Transmit(canAgent.addr << 5 | 0x0b,CAN_ID_STD | CAN_RTR_DATA);
    }

    void ClearErrors() {
        canAgent[0] = 0x00;
        canAgent[1] = 0x00;
        canAgent[2] = 0x00;
        canAgent[3] = 0x00;
        canAgent[4] = 0x00;
        canAgent[5] = 0x00;
        canAgent[6] = 0x00;
        canAgent[7] = 0x00;
        canAgent.Transmit(canAgent.addr << 5 | 0x18,CAN_ID_STD | CAN_RTR_DATA);
    }

    void MessageGenerate() {

        switch (params.ctrlType) {
            case Motor_Ctrl_Type_e::Torque: {
                float txTorque = Clamp(1 * controller->GetOutput(), -2000.f, 2000.f);
                volatile uint32_t txTorqueFloat = *reinterpret_cast<uint32_t*>(&txTorque);

                for (int i = 0; i < 4; ++i) {
                    canAgent[i] = (txTorqueFloat >> (i * 8)) & 0xFF;
                }
                canAgent[4] = 0x00;
                canAgent[5] = 0x00;
                canAgent[6] = 0x00;
                canAgent[7] = 0x00;
                canAgent.Transmit(canAgent.addr << 5 | 0x00e,CAN_ID_STD | CAN_RTR_DATA);
                break;
            }
            case Motor_Ctrl_Type_e::Position: {
                // float pos = controller->GetOutput()/360.0f;
                // uint32_t pos_binary = *reinterpret_cast<uint32_t*>(&pos);
                //
                // for (int i = 0; i < 4; ++i) {
                //     canAgent[i] = (pos_binary >> (i * 8)) & 0xFF;
                // }
                // canAgent[4] = 0x00;
                // canAgent[5] = 0x00;
                // canAgent[6] = 0x00;
                // canAgent[7] = 0x00;
                // canAgent.Transmit(canAgent.addr << 5 | 0x00c,CAN_ID_STD | CAN_RTR_DATA);
                // break;
                float txSpeed = controller->GetOutput();
                uint32_t txSpeedFloat = *reinterpret_cast<uint32_t*>(&txSpeed);

                for (int i = 0; i < 4; ++i) {
                    canAgent[i] = (txSpeedFloat >> (i * 8)) & 0xFF;
                }
                canAgent[4] = 0x00;
                canAgent[5] = 0x00;
                canAgent[6] = 0x00;
                canAgent[7] = 0x00;
                canAgent.Transmit(canAgent.addr << 5 | 0x00d,CAN_ID_STD | CAN_RTR_DATA);
                break;
            }
            case Motor_Ctrl_Type_e::Speed: {
                float txSpeed = controller->GetOutput();
                uint32_t txSpeedFloat = *reinterpret_cast<uint32_t*>(&txSpeed);

                for (int i = 0; i < 4; ++i) {
                    canAgent[i] = (txSpeedFloat >> (i * 8)) & 0xFF;
                }
                canAgent[4] = 0x00;
                canAgent[5] = 0x00;
                canAgent[6] = 0x00;
                canAgent[7] = 0x00;
                canAgent.Transmit(canAgent.addr << 5 | 0x00d,CAN_ID_STD | CAN_RTR_DATA);
                break;
            }
        }
        // canAgent.Send(canAgent.addr, CAN_ID_STD | CAN_RTR_REMOTE); //��ȡ������
    }

    void Update() {
        uint32_t position_data = (canAgent.rxbuf[0] | (canAgent.rxbuf[1] << 8u) | (canAgent.rxbuf[2] << 16u) | (canAgent.rxbuf[3] << 24u));
        float position_float = *reinterpret_cast<float*>(&position_data);
        state.position = position_float;

        uint32_t speed_data = (canAgent.rxbuf[4] | (canAgent.rxbuf[5] << 8u) | (canAgent.rxbuf[6] << 16u) | (canAgent.rxbuf[7] << 24u));
        float speed_float = *reinterpret_cast<float*>(&speed_data);
        state.speed = speed_float;
    }
};

#endif
