/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef V5_SUB_HPP
#define V5_SUB_HPP

#define PRESSURE_SENSORS_INIT_SAMPLE_TIMES 1000
#define MOTOR_COUNT 8
#define PRESSURE_SENSOR_COUNT 4

#include "FillLight/SUBLAB_FillLight.hpp"
#include "ESC_Motors/ESC_Motor.hpp"
#include "PressureSensor/PressureSensorBase.hpp"
#include "IMUBase.hpp"
#include <array>
#include "Clamp.hpp"
#include "arm_math.h"
#include "Matrix/matrix.h"
#include "Control/PID.hpp"
#include "Verification/CRC.h"

struct SUB_Motor_t {
    ESC_Motor *motor;
    float lx;
    float ly;
    float lz;
};

struct SUB_Pressure_Sensor_t {
    PressureSensorBase *sensor;
    float lx;
    float ly;
    float lz;
};


class V5_SUB;

// V5_SUBBuilder 类定义
class V5_SUBBuilder {
public:
    V5_SUBBuilder() = default;

    V5_SUBBuilder& AddMotor(ESC_Motor* motor, float x, float y, float z) {
        if (motorCount < MOTOR_COUNT) {
            motors[motorCount++] = {motor, x, y, z};
        }
        return *this;
    }

    V5_SUBBuilder& AddPressureSensor(PressureSensorBase* sensor, float x, float y, float z) {
        if (sensorCount < PRESSURE_SENSOR_COUNT) {
            pressureSensors[sensorCount++] = {sensor, x, y, z};
        }
        return *this;
    }

    V5_SUBBuilder& AddIMU(IMUBase* imu) {
        this->imu = imu;
        return *this;
    }

    V5_SUBBuilder& AddController(ControllerBase* rollController_, ControllerBase* pitchController_, ControllerBase* yawController_, ControllerBase* deepthController_) {
        this->rollController = rollController_;
        this->pitchController = pitchController_;
        this->yawController = yawController_;
        this->deepthController = deepthController_;
        return *this;
    }

    V5_SUB* Build();

    std::array<SUB_Motor_t, MOTOR_COUNT> motors{};
    size_t motorCount = 0;

    std::array<SUB_Pressure_Sensor_t, PRESSURE_SENSOR_COUNT> pressureSensors{};
    size_t sensorCount = 0;

    IMUBase* imu = nullptr;

    ControllerBase* rollController;
    ControllerBase* pitchController;
    ControllerBase* yawController;
    ControllerBase* deepthController;
};


class V5_SUB : public DeviceBase {
public:
    // 使用固定参数列表的构造函数
    explicit V5_SUB(V5_SUBBuilder const &temp) {
        this->motors = temp.motors;
        this->pressureSensors = temp.pressureSensors;
        this->imu = temp.imu;
        this->rollController = temp.rollController;
        this->pitchController = temp.pitchController;
        this->yawController = temp.yawController;
        this->deepthController = temp.deepthController;

        rollController->SetFeedback({&currentAngleRate[0][0]});
        pitchController->SetFeedback({&currentAngleRate[1][0]});
        yawController->SetFeedback({&currentAngleRate[2][0]});
        deepthController->SetFeedback({&currentDeepth});
        rollController->SetTarget(&targetAngleRate[0][0]);
        pitchController->SetTarget(&targetAngleRate[1][0]);
        yawController->SetTarget(&targetAngleRate[2][0]);
        deepthController->SetTarget(&targetDeepth);

        A = Matrixf<4,3>{motors[1].ly, -motors[1].lx, -1,
                            motors[2].ly, -motors[2].lx, -1,
                            motors[5].ly, -motors[5].lx, -1,
                            motors[6].ly, -motors[6].lx, -1};

        B = Matrixf<4, 3>{1, -1, 1,
                            -1, 1, 1,
                            1, 1, -1,
                            -1, -1, -1};
    }

    void EnableMotors() {
        for (auto &motor : motors) {
            motor.motor->EnableMotor();
        }
    }

    void DisableMotors() {
        for (auto &motor : motors) {
            motor.motor->DisableMotor();
        }
    }

    void Disarm() {
        state = SUB_STATE::STABILIZING;
    }

    void Command(float yawRate, float FBSpeed, float LRSpeed, float downSpeed, float upSpeed, uint8_t startButton) {
        targetDeepth += (downSpeed - upSpeed) * 0.001f * 0.1f;
        targetDeepth = Clamp(targetDeepth, 0.0f, 10.0f);
        targetAttitude[2][0] += yawRate * 0.001f * 0.4f;
        targetVel[0][0] = FBSpeed * 0.35f;
        targetVel[1][0] = LRSpeed * 0.35f;
        SwitchState(startButton);
    }

    void Handle() final {

        Update();//在更新控制器前先更新误差

        switch (state) {
            case SUB_STATE::INIT:
                PressureSensorInit();
                IMUInit();
                if (pressureInitFinished && imuInitFinished) {
                    state = SUB_STATE::IDLE;
                }
                break;
            case SUB_STATE::IDLE:
                break;
            case SUB_STATE::STABILIZING:
                StabilizeMode();
                rollController->Calc();
                pitchController->Calc();
                yawController->Calc();
                deepthController->Calc();
                MotorPowerDistribution();
                break;
            case SUB_STATE::POSITION_HOLDING:
                break;
            default:
                break;
        }

        static uint8_t cnt = 0;
        cnt++;
        if(cnt >= 10) {
            cnt = 0;
            uploadData.roll = currentAttitude[0][0];
            uploadData.pitch = currentAttitude[1][0];
            uploadData.yaw = currentAttitude[2][0];
            uploadData.deepth = currentDeepth;
            uploadData.targetDeepth = targetDeepth;
            uploadData.currentRollRate = currentAngleRate[0][0];
            uploadData.currentPitchRate = currentAngleRate[1][0];
            uploadData.currentYawRate = currentAngleRate[2][0];
            uploadData.targetRollRate = targetAngleRate[0][0];
            uploadData.targetPitchRate = targetAngleRate[1][0];
            uploadData.targetYawRate = targetAngleRate[2][0];
            uploadData.targetPitch = targetAttitude[2][0];
            uploadData.pitchOutput = pitchController->GetOutput();
            uploadData.targetFBvel = targetVel[0][0];
            uploadData.targetLRvel = targetVel[1][0];
            memcpy(txBuffer, &uploadData, 64);
            UART_Base<3>::GetInstance().Transmit(txBuffer, 64);
        }
    }

private:
    enum class SUB_STATE {
        INIT = 0X00,
        IDLE = 0X01,
        STABILIZING = 0X02,
        POSITION_HOLDING = 0X03
    }state = SUB_STATE::INIT;

    struct UploadData {
        float roll{0.0f};
        float pitch{0.0f};
        float yaw{0.0f};
        float deepth{0.0f};
        float targetDeepth{0.0f};
        float currentRollRate{0.0f};
        float currentPitchRate{0.0f};
        float currentYawRate{0.0f};
        float targetRollRate{0.0f};
        float targetPitchRate{0.0f};
        float targetYawRate{0.0f};
        float targetPitch{0.0f};
        float pitchOutput{0.0f};
        float targetFBvel{0.0f};
        float targetLRvel{0.0f};
        uint8_t tail[4]{0x00, 0x00, 0x80, 0x7f};
    }uploadData __packed;


    uint8_t txBuffer[100]{};

    std::array<SUB_Motor_t, MOTOR_COUNT> motors{};
    std::array<SUB_Pressure_Sensor_t, PRESSURE_SENSOR_COUNT> pressureSensors{};
    IMUBase *imu = nullptr;
    std::array<float, PRESSURE_SENSOR_COUNT> pressureSensorOffset = {102000.0f + 2600.0f, 101900.0f + 2600.0f, 101600.0f + 2600.0f, 102000.0f + 2600.0f};
    bool pressureInitFinished = false;
    bool imuInitFinished = false;
    Matrixf<3, 1> targetAttitude{};//欧拉角
    Matrixf<3, 1> targetAngleRate{};
    Matrixf<3, 1> currentAngleRate{};
    Matrixf<3, 1> currentAttitude{};
    Matrixf<3, 1> rollPitchDeepthControllerOutput{};
    Matrixf<3, 1> yawFbLrControllerOutput{};
    Matrixf<4,3> A{};
    Matrixf<4,3> B{};
    Matrixf<2, 1> targetVel{};//FB LR
    float targetDeepth{0.0f}; //默认水压计平面深度
    float currentDeepth{0.0f};


    //控制器
    ControllerBase* rollController;
    ControllerBase* pitchController;
    ControllerBase* yawController;
    ControllerBase* deepthController;

    /*** 水压计初始化，多次采样取平均offset ***/
    void PressureSensorInit() {
        // static std::array<float, PRESSURE_SENSOR_COUNT> pressureSampleSum = {0.0f};
        // static uint16_t sampleTimes = 0;

        if (pressureInitFinished) {
            return;
        }

        // 检查所有传感器是否有数据
        for (size_t i = 0; i < PRESSURE_SENSOR_COUNT; i++) {
            // if (pressureSensors[i].sensor->GetPressure() < 1.0f) {
            //     return; // 传感器无数据，跳过采样
            // }
            pressureInitFinished = true;
        }

        // // 累积所有传感器的采样值
        // for (size_t i = 0; i < PRESSURE_SENSOR_COUNT; i++) {
        //     pressureSampleSum[i] += pressureSensors[i].sensor->GetPressure();
        // }
        // sampleTimes++;
        //
        // if (sampleTimes == PRESSURE_SENSORS_INIT_SAMPLE_TIMES) {
        //     // 计算平均值作为offset
        //     for (size_t i = 0; i < PRESSURE_SENSOR_COUNT; i++) {
        //         pressureSensorOffset[i] = pressureSampleSum[i] / PRESSURE_SENSORS_INIT_SAMPLE_TIMES;
        //     }
        //     pressureInitFinished = true;
        // }
    }

    void IMUInit() {
        if(imuInitFinished) {
            return;
        }
        if(imu->IsDataGet()) {
            imuInitFinished = true;
            // targetAttitude = Matrixf<3,1>(imu->getEulerArray().data());
            targetAttitude[2][0] = imu->getEulerArray()[2];
        }
    }

    float SqrtControler(float error, float errorLimit, float accLimit, float p) {
        if(error > errorLimit) {
            error = errorLimit;
        }
        else if(error < -errorLimit) {
            error = -errorLimit;
        }

        if(errorLimit < 1e-6f) {
            // 二阶限制为零或负值，使用纯比例控制
            return error * p;
        }
        else if(p < 1e-6f) {
            // P项为零，但存在二阶限制
            if(error > 1e-6f) {
                return sqrtf(2 * accLimit * error);
            }
            else if (error < -1e-6f) {
                return -sqrtf(-2 * accLimit * error);
            }
            else {
                return 0.0f;
            }
        }
        else {
            // 同时存在P项和二阶限制
            float linear_dist = accLimit / (p * p);

            if(error > linear_dist) {
                return sqrtf(2.0 * accLimit * (error - (linear_dist / 2.0)));
            }
            else if (error < -linear_dist) {
                return -sqrtf(2.0 * accLimit * (-error - (linear_dist / 2.0)));
            }
            else {
                return error * p;
            }
        }
    }

    void Update() {
        Matrixf<3,1> attitudeError = targetAttitude - imu->getEulerArray().data();
        targetAngleRate[0][0] = SqrtControler(attitudeError[0][0], 2.0f, 1.0f, 5.0f);
        targetAngleRate[1][0] = SqrtControler(attitudeError[1][0], 2.0f, 1.0f, 5.0f);
        targetAngleRate[2][0] = SqrtControler(attitudeError[2][0], 2.0f, 1.0f, 5.0f);
        currentAngleRate = imu->getAngleRateArray().data();
        currentAttitude = imu->getEulerArray().data();

        //更新深度
        float waterPressure = ((pressureSensors[1].sensor->GetPressure() - pressureSensorOffset[1]) + (pressureSensors[3].sensor->GetPressure() - pressureSensorOffset[3]))/2;
        currentDeepth = waterPressure / 9.8f / 1000.f;
    }

    //电机推力分配
    void MotorPowerDistribution() {
        float rollOutput = Clamp(1 * rollController->GetOutput(), -0.2f, 0.2f);
        float pitchOutput = Clamp(1 * pitchController->GetOutput(), -0.2f, 0.2f);
        float yawOutput = Clamp(1 * yawController->GetOutput(), -0.2f, 0.2f);
        float deepthOutput = Clamp(1 * deepthController->GetOutput(), -0.5f, 0.5f);

        //垂直电机推力分配
        rollPitchDeepthControllerOutput[0][0] = rollOutput;
        rollPitchDeepthControllerOutput[1][0] = pitchOutput;
        rollPitchDeepthControllerOutput[2][0] = deepthOutput;

        Matrixf<4,1> upperMotorOutPut = A * rollPitchDeepthControllerOutput;
        upperMotorOutPut[0][0] = fabsf(upperMotorOutPut[0][0]) < 0.01f ? 0.0f : upperMotorOutPut[0][0];
        upperMotorOutPut[1][0] = fabsf(upperMotorOutPut[1][0]) < 0.01f ? 0.0f : upperMotorOutPut[1][0];
        upperMotorOutPut[2][0] = fabsf(upperMotorOutPut[2][0]) < 0.01f ? 0.0f : upperMotorOutPut[2][0];
        upperMotorOutPut[3][0] = fabsf(upperMotorOutPut[3][0]) < 0.01f ? 0.0f : upperMotorOutPut[3][0];

        //水平电机推力分配
        yawFbLrControllerOutput[0][0] = yawOutput;
        yawFbLrControllerOutput[1][0] = targetVel[0][0];
        yawFbLrControllerOutput[2][0] = targetVel[1][0];

        Matrixf<4,1> lowerMotorOutPut = B * yawFbLrControllerOutput;
        lowerMotorOutPut[0][0] = fabsf(lowerMotorOutPut[0][0]) < 0.01f ? 0.0f : lowerMotorOutPut[0][0];
        lowerMotorOutPut[1][0] = fabsf(lowerMotorOutPut[1][0]) < 0.01f ? 0.0f : lowerMotorOutPut[1][0];
        lowerMotorOutPut[2][0] = fabsf(lowerMotorOutPut[2][0]) < 0.01f ? 0.0f : lowerMotorOutPut[2][0];
        lowerMotorOutPut[3][0] = fabsf(lowerMotorOutPut[3][0]) < 0.01f ? 0.0f : lowerMotorOutPut[3][0];

        motors[1].motor->SetThrottle(upperMotorOutPut[0][0]);
        motors[2].motor->SetThrottle(upperMotorOutPut[1][0]);
        motors[5].motor->SetThrottle(upperMotorOutPut[2][0]);
        motors[6].motor->SetThrottle(upperMotorOutPut[3][0]);

        motors[0].motor->SetThrottle(lowerMotorOutPut[0][0]);
        motors[3].motor->SetThrottle(lowerMotorOutPut[1][0]);
        motors[4].motor->SetThrottle(lowerMotorOutPut[2][0]);
        motors[7].motor->SetThrottle(lowerMotorOutPut[3][0]);
    }

    /*** 水平姿态保持模式 ***/
    void StabilizeMode() {
    }

    /*** 全向姿态保持模式 ***/
    void PositionHoldMode() {
    }

    void SwitchState(uint8_t buttonState) {
        static uint8_t lastButtonState = 0;
        if(buttonState != lastButtonState &&  buttonState == 1) {
            if(state == SUB_STATE::IDLE) {
                EnableMotors();
                targetAttitude[2][0] = currentAttitude[2][0];
                state = SUB_STATE::STABILIZING;
            }
            else if(state == SUB_STATE::STABILIZING) {
                DisableMotors();
                state = SUB_STATE::IDLE;
            }
        }
        lastButtonState = buttonState;
    }
};


V5_SUB* V5_SUBBuilder::Build() {
    return new V5_SUB(*this);
}

#endif //V5_SUB_HPP