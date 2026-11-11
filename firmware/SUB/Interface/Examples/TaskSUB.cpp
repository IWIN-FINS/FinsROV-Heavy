/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#include "Bus/DSHOT.hpp"
#include "Bus/UART_Base.hpp"
#include "DSHOT_Motor.hpp"
#include "IMU/H30_IMU.hpp"
#include "PressureSensor/XS_PressureSensor.hpp"
#include "SUB/V5_SUB.hpp"
#include "SUBLAB_FillLight.hpp"
#include "Task.h"
#include "V5Streamer/Streamer.hpp"
#include "ServoMotors/AU25S500.hpp"



#define M1 3//1号电机
#define M2 7//2号电机
#define M3 5//3号电机
#define M4 4//4号电机
#define M5 2//5号电机
#define M6 6//6号电机
#define M7 8 //7号电机
#define M8 1//8号电机

#define L1 10 //补光灯
#define L2 11
#define L3 12

// AU25S500<6> servo1(0x00, 0);
// AU25S500<6> servo2(0x01, 0);
// AU25S500<6> servo3(0x02, 0);
// AU25S500<6> camYawServo(0x01, 0);

ESC_Motor* motorLFLower = &DSHOT_Motor<M1>::GetInstance();
ESC_Motor* motorLFUpper = &DSHOT_Motor<M2>::GetInstance();
ESC_Motor* motorLBUpper = &DSHOT_Motor<M3>::GetInstance();
ESC_Motor* motorLBLower = &DSHOT_Motor<M4>::GetInstance();
ESC_Motor* motorRBLower = &DSHOT_Motor<M5>::GetInstance();
ESC_Motor* motorRBUpper = &DSHOT_Motor<M6>::GetInstance();
ESC_Motor* motorRFUpper = &DSHOT_Motor<M7>::GetInstance();
ESC_Motor* motorRFLower = &DSHOT_Motor<M8>::GetInstance();

/*** 上位机数据 ***/
Streamer v5streamer;
UARTBuffer<3, 30> uart3Buffer([](uint8_t* data, size_t length) {
    v5streamer.Decode(data, length);
});

uint8_t data_t[9]{0X59 , 0X53 , 0X4D , 0X12 , 0X00 , 0X02 , 0X02 , 0X63, 0XCF};
/*** IMU数据 ***/
H30_IMU imu;
UARTBuffer<7, 100> uart7Buffer([](uint8_t* data, size_t length) {
    imu.Decode(data, length);
});

/*** 控制器 ***/
constexpr PID_Param_t rollRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto rollRateController = CreateControllers<PID, 1>(rollRatePID);

constexpr PID_Param_t pitchRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto pitchRateController = CreateControllers<PID, 1>(pitchRatePID);

constexpr PID_Param_t yawRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto yawRateController = CreateControllers<PID, 1>(yawRatePID);

constexpr PID_Param_t deepthPID = {0.8f, 0.001f, 0.0f, 100, 0.5};
auto deepthController = CreateControllers<PID, 1>(deepthPID);

XS_PressureSensor<8> pressureSensor1(0x01);
XS_PressureSensor<8> pressureSensor2(0x02);
XS_PressureSensor<8> pressureSensor3(0x03);
XS_PressureSensor<8> pressureSensor4(0x04);

V5_SUB* sub = V5_SUBBuilder().AddMotor(motorLFLower, 0.0f, 0.0f, 0.0f).
                                AddMotor(motorLFUpper, 1.0f, 1.0f, 0.0f).
                                AddMotor(motorLBUpper, -1.0f, 1.0f, 0.0f).
                                AddMotor(motorLBLower, 0.0f, 0.0f, 0.0f).
                                AddMotor(motorRBLower, 0.0f, 0.0f, 0.0f).
                                AddMotor(motorRBUpper, -1.0f, -1.0f, 0.0f).
                                AddMotor(motorRFUpper, 1.0f, -1.0f, 0.0f).
                                AddMotor(motorRFLower, 0.0f, 0.0f, 0.0f).
                                AddPressureSensor(&pressureSensor1, 0.0f, 0.0f, 0.0f).
                                AddPressureSensor(&pressureSensor2, 0.0f, 0.0f, 0.0f).
                                AddPressureSensor(&pressureSensor3, 0.0f, 0.0f, 0.0f).
                                AddPressureSensor(&pressureSensor4, 0.0f, 0.0f, 0.0f).
                                AddIMU(&imu).
                                AddController(&rollRateController[0],&pitchRateController[0],&yawRateController[0],&deepthController[0]).Build();


float camYawAngle{0};
float camPitchAngle{0};

void TaskTest() {
    camYawAngle += static_cast<float>(v5streamer.joystickData.camYaw) * 0.01f;
    camPitchAngle += static_cast<float>(v5streamer.joystickData.camPitch) * 0.01f;
    Clamp(camYawAngle, -40.f, 40.f);
    Clamp(camPitchAngle, -30.f, 30.f);


    sub->Command(v5streamer.joystickData.yawRate,
        v5streamer.joystickData.forwardSpeed,
        v5streamer.joystickData.leftRightSpeed,
        v5streamer.joystickData.downSpeed,
        v5streamer.joystickData.upSpeed,
        v5streamer.joystickData.startButton);

    static uint8_t lastState = 0;
    if (v5streamer.joystickData.camFillLight) {
        static bool camLightState = false;
        if(lastState != v5streamer.joystickData.camFillLight) {
            camLightState = !camLightState;
        }
        SUBLAB_FillLight<L1>::GetInstance().SetBrightness(camLightState ? 0.5f : 0.0f);
        SUBLAB_FillLight<L2>::GetInstance().SetBrightness(camLightState ? 0.5f : 0.0f);
        SUBLAB_FillLight<L3>::GetInstance().SetBrightness(camLightState ? 0.5f : 0.0f);
    }
    lastState = v5streamer.joystickData.camFillLight;

}
TASK_EXPORT(TaskTest);