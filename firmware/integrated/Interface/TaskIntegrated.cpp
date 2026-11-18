/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#include <cmath>

#include "Bus/DSHOT.hpp"
#include "Bus/UART_Base.hpp"
#include "DSHOT_Motor.hpp"
#include "IMU/H30_IMU.hpp"
#include "IntegratedPressure.hpp"
#include "IntegratedVehicle.hpp"
#include "usart.h"
#include "SensorGate.hpp"
#include "IntegratedPID.hpp"
#include "SUBLAB_FillLight.hpp"
#include "Task.h"
#include "V5Streamer/Streamer.hpp"
#include "ServoMotors/AU25S500.hpp"
#include "Battery/BatteryBase.hpp"
#ifndef FINS_DEPTH_CALIBRATED
#define FINS_DEPTH_CALIBRATED 0
#endif



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

uint8_t data_t[9]{0X59 , 0X53 , 0X4D , 0X12 , 0X00 , 0X02 , 0X02 , 0X63, 0XCF};
/*** IMU数据 ***/
H30_IMU imu;
uint32_t imuValidTick=0;
bool imuValid=false;
UARTBuffer<7, 100> uart7Buffer([](uint8_t* data, size_t length) {
    if(!fins::validH30(data,length)) return;
    imu.Decode(data, length);
    for(float value:imu.getEulerArray()) if(!std::isfinite(value)) {imuValid=false;return;}
    for(float value:imu.getAccelArray()) if(!std::isfinite(value)) {imuValid=false;return;}
    for(float value:imu.getAngleRateArray()) if(!std::isfinite(value)) {imuValid=false;return;}
    imuValid=true;imuValidTick=HAL_GetTick();
});

Battery<1> battery(0x01);

/*** 控制器 ***/
constexpr PID_Param_t rollRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto rollRateController = CreateControllers<IntegratedPID, 1>(rollRatePID);

constexpr PID_Param_t pitchRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto pitchRateController = CreateControllers<IntegratedPID, 1>(pitchRatePID);

constexpr PID_Param_t yawRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto yawRateController = CreateControllers<IntegratedPID, 1>(yawRatePID);

constexpr PID_Param_t deepthPID = {0.2f, 0.0005f, 0.0f, 100, 0.5};
auto deepthController = CreateControllers<IntegratedPID, 1>(deepthPID);

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
                                AddBattery(&battery).
                                AddController(&rollRateController[0],&pitchRateController[0],&yawRateController[0],&deepthController[0]).Build();

namespace {
// RX ISR only copies bytes; parser and actuator transitions run in TaskIntegrated.
uint8_t rxRing[2048]{};
volatile uint16_t rxHead=0,rxTail=0;
volatile bool rxOverflow=false;
UARTBuffer<3,256> commands([](uint8_t* data,size_t n) {
    for(size_t i=0;i<n;++i) {
        const uint16_t next=(rxHead+1)%sizeof(rxRing);
        if(next==rxTail) {rxOverflow=true;break;}
        rxRing[rxHead]=data[i];rxHead=next;
    }
});
uint8_t txFrames[16][MAVLINK_MAX_PACKET_LEN]{};
uint16_t txLengths[16]{};
uint8_t txHead=0,txTail=0;
bool txBusy=false,txOverflow=false;
void sendFrame(const uint8_t* data,uint16_t length) {
    const uint8_t next=(txHead+1)%16;
    if(next==txTail) {txOverflow=true;return;}
    std::memcpy(txFrames[txHead],data,length);txLengths[txHead]=length;txHead=next;
}
void pumpTx() {
    if(txBusy && huart3.gState==HAL_UART_STATE_READY) {txBusy=false;txTail=(txTail+1)%16;}
    if(!txBusy && txTail!=txHead && HAL_UART_Transmit_DMA(&huart3,txFrames[txTail],txLengths[txTail])==HAL_OK) txBusy=true;
}
uint64_t micros() {
    static uint32_t previous=0;static uint64_t total=0;
    const uint32_t tick=HAL_GetTick();total+=static_cast<uint32_t>(tick-previous);previous=tick;
    return total*1000;
}
uint64_t bootSession() {
    // STM32 hardware random source, checked before any controller is accepted.
    __HAL_RCC_RNG_CLK_ENABLE();RNG->CR |= RNG_CR_RNGEN;
    uint64_t result=0;
    for(unsigned i=0;i<2;++i) {
        const uint32_t start=HAL_GetTick();
        while(!(RNG->SR & RNG_SR_DRDY)) if(HAL_GetTick()-start>10) return 0;
        if(RNG->SR & (RNG_SR_CECS|RNG_SR_SECS)) return 0;
        result=(result<<32)|RNG->DR;
    }
    return result;
}
bool sensorsFresh() {
    const uint32_t now=HAL_GetTick();
    return fins::fresh(now,imuValidTick,100,imuValid) && pressureSensor1.Fresh(now) && pressureSensor2.Fresh(now)
        && pressureSensor3.Fresh(now) && pressureSensor4.Fresh(now);
}
bool apply(const fins::Control& state) {
    if(state.armed && !sensorsFresh()) return false;
    static fins::Control previous{};
    if(!sub->ApplyIntegrated(state)) return false;
    if(!state.active || state.epoch!=previous.epoch || state.mode!=previous.mode || !previous.active) {
        rollRateController[0].Reset();pitchRateController[0].Reset();yawRateController[0].Reset();
    }
    if(!state.hold || !previous.hold || state.epoch!=previous.epoch) deepthController[0].Reset();
    previous=state;
    return true;
}
}
void TaskIntegrated() {
    static const uint64_t boot=bootSession();
    static fins::Endpoint endpoint(boot,apply,sendFrame,FINS_DEPTH_CALIBRATED);
    static uint64_t previous=micros(),lastStatus=0,lastTelemetry=0;
    const uint64_t now=micros();
    if(!boot) {endpoint.stop(4);return;}
    if(rxOverflow || txOverflow) {
        endpoint.stop(8);rxTail=rxHead;rxOverflow=false;txOverflow=false;
    }
    endpoint.tick(now);
    if(endpoint.state.armed && !sensorsFresh()) endpoint.stop(16);
    uint8_t chunk[256];size_t n=0;
    while(rxTail!=rxHead && n<sizeof(chunk)) {chunk[n++]=rxRing[rxTail];rxTail=(rxTail+1)%sizeof(rxRing);}
    if(n) endpoint.feed(chunk,n,now);
    float dt=static_cast<float>(now-previous)*1e-6f;previous=now;
    sub->IntegratedStep(Clamp(dt,0.f,0.01f));
    if(now-lastStatus>=100000) {endpoint.status();lastStatus=now;}
    if(now-lastTelemetry>=5000) {
        mavlink_fins_telemetry_t values{};sub->FillTelemetry(values,boot,now);
        mavlink_message_t message{};mavlink_msg_fins_telemetry_encode(1,1,&message,&values);
        endpoint.transmit(message);lastTelemetry=now;
    }
    pumpTx();
}
TASK_EXPORT(TaskIntegrated);
