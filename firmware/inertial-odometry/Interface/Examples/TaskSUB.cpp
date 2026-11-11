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
#include "PressureSensor/XS_PressureSensor.hpp"
#include "SUB/V5_SUB.hpp"
#include "SUBLAB_FillLight.hpp"
#include "Task.h"
#include "V5Streamer/Streamer.hpp"
#include "ServoMotors/AU25S500.hpp"
#include "Battery/BatteryBase.hpp"



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
UARTBuffer<3, 60> uart3Buffer([](uint8_t* data, size_t length) {
    v5streamer.Decode(data, length);
});

uint8_t data_t[9]{0X59 , 0X53 , 0X4D , 0X12 , 0X00 , 0X02 , 0X02 , 0X63, 0XCF};
/*** IMU数据 ***/
H30_IMU imu;
UARTBuffer<7, 100> uart7Buffer([](uint8_t* data, size_t length) {
    imu.Decode(data, length);
});

Battery<1> battery(0x01);

/*** 控制器 ***/
constexpr PID_Param_t rollRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto rollRateController = CreateControllers<PID, 1>(rollRatePID);

constexpr PID_Param_t pitchRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto pitchRateController = CreateControllers<PID, 1>(pitchRatePID);

constexpr PID_Param_t yawRatePID = {0.2f, 0.001f, 0.0f, 100, 2000};
auto yawRateController = CreateControllers<PID, 1>(yawRatePID);

constexpr PID_Param_t deepthPID = {0.2f, 0.0005f, 0.0f, 100, 0.5};
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
                                AddBattery(&battery).
                                AddController(&rollRateController[0],&pitchRateController[0],&yawRateController[0],&deepthController[0]).Build();


float camYawAngle{0};
float camPitchAngle{0};

namespace {

constexpr float kPi = 3.14159265358979323846f;
constexpr float kHalfPi = kPi / 2.0f;
constexpr float kMaxPathSpeed = 0.3f;
constexpr float kPathAcceleration = 0.3f;
constexpr float kSettleSpeed = 0.08f;
constexpr float kPositionKp = 0.5f;
constexpr float kVelocityTrackingKp = 1.0f;  // throttle / (m/s)
constexpr float kPathThrottleLimit = 0.3f;
constexpr float kPositionTolerance = 0.04f;
constexpr float kYawTolerance = 0.05f;
constexpr uint32_t kPoseTimeoutMs = 200;

enum class TrajectoryType { Square, Circle };
constexpr TrajectoryType kSelectedTrajectory = TrajectoryType::Square;
// constexpr TrajectoryType kSelectedTrajectory = TrajectoryType::Circle;

struct GlobalPose {
    float x;
    float y;
    float yaw;
    float xVelocity;
    float yVelocity;
    float yawRate;
};

struct TrajectoryCommand {
    float globalXVelocity = 0.0f;
    float globalYVelocity = 0.0f;
    float targetYaw = 0.0f;
};

class TrapezoidalProfile {
public:
    void Reset(float distance) {
        distance_ = distance;
        const float nominalAccelTime = kMaxPathSpeed / kPathAcceleration;
        const float nominalAccelDistance = 0.5f * kPathAcceleration * nominalAccelTime * nominalAccelTime;

        if (2.0f * nominalAccelDistance >= distance_) {
            accelTime_ = std::sqrt(distance_ / kPathAcceleration);
            peakSpeed_ = kPathAcceleration * accelTime_;
            cruiseTime_ = 0.0f;
        } else {
            accelTime_ = nominalAccelTime;
            peakSpeed_ = kMaxPathSpeed;
            cruiseTime_ = (distance_ - 2.0f * nominalAccelDistance) / peakSpeed_;
        }
        totalTime_ = 2.0f * accelTime_ + cruiseTime_;
    }

    void Sample(float elapsed, float& distance, float& speed, bool& finished) const {
        if (elapsed <= 0.0f) {
            distance = 0.0f;
            speed = 0.0f;
            finished = false;
            return;
        }

        if (elapsed < accelTime_) {
            distance = 0.5f * kPathAcceleration * elapsed * elapsed;
            speed = kPathAcceleration * elapsed;
            finished = false;
            return;
        }

        const float accelDistance = 0.5f * kPathAcceleration * accelTime_ * accelTime_;
        if (elapsed < accelTime_ + cruiseTime_) {
            distance = accelDistance + peakSpeed_ * (elapsed - accelTime_);
            speed = peakSpeed_;
            finished = false;
            return;
        }

        if (elapsed < totalTime_) {
            const float decelElapsed = elapsed - accelTime_ - cruiseTime_;
            distance = accelDistance + peakSpeed_ * cruiseTime_ +
                       peakSpeed_ * decelElapsed - 0.5f * kPathAcceleration * decelElapsed * decelElapsed;
            speed = peakSpeed_ - kPathAcceleration * decelElapsed;
            finished = false;
            return;
        }

        distance = distance_;
        speed = 0.0f;
        finished = true;
    }

private:
    float distance_ = 0.0f;
    float accelTime_ = 0.0f;
    float cruiseTime_ = 0.0f;
    float peakSpeed_ = 0.0f;
    float totalTime_ = 0.0f;
};

class PlanarTrajectory {
public:
    void Start(TrajectoryType type, const GlobalPose& pose, uint32_t nowTick) {
        type_ = type;
        startPose_ = pose;
        segmentStart_ = pose;
        state_ = type == TrajectoryType::Square ? State::SquareMoving : State::CircleMoving;
        squareSide_ = 0;
        stateStartTick_ = nowTick;

        if (type == TrajectoryType::Square) {
            profile_.Reset(1.0f);
        } else {
            circleCenterX_ = pose.x - 0.5f * std::sin(pose.yaw);
            circleCenterY_ = pose.y + 0.5f * std::cos(pose.yaw);
            profile_.Reset(2.0f * kPi * 0.5f);
        }
        command_.targetYaw = pose.yaw;
    }

    void Cancel() {
        state_ = State::Idle;
        command_ = {};
    }

    bool IsFinished() const { return state_ == State::Finished; }

    const TrajectoryCommand& Update(const GlobalPose& pose, uint32_t nowTick) {
        switch (state_) {
            case State::SquareMoving:
                UpdateSquareMoving(pose, nowTick);
                break;
            case State::SquareTurning:
                UpdateSquareTurning(pose, nowTick);
                break;
            case State::CircleMoving:
                UpdateCircleMoving(pose, nowTick);
                break;
            case State::Finished:
                command_.globalXVelocity = 0.0f;
                command_.globalYVelocity = 0.0f;
                break;
            case State::Idle:
                break;
        }
        return command_;
    }

private:
    enum class State { Idle, SquareMoving, SquareTurning, CircleMoving, Finished };

    static float NormalizeAngle(float angle) {
        constexpr float kTwoPi = 2.0f * kPi;
        while (angle > kPi) angle -= kTwoPi;
        while (angle < -kPi) angle += kTwoPi;
        return angle;
    }

    static float Distance(const GlobalPose& pose, float x, float y) {
        const float dx = x - pose.x;
        const float dy = y - pose.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void SetTrackingVelocity(const GlobalPose& pose, float targetX, float targetY,
                             float feedforwardX, float feedforwardY, float allowedSpeed) {
        float velocityX = feedforwardX + (targetX - pose.x) * kPositionKp;
        float velocityY = feedforwardY + (targetY - pose.y) * kPositionKp;
        const float speed = std::sqrt(velocityX * velocityX + velocityY * velocityY);
        if (speed > allowedSpeed && speed > 0.0f) {
            const float scale = allowedSpeed / speed;
            velocityX *= scale;
            velocityY *= scale;
        }
        command_.globalXVelocity = velocityX;
        command_.globalYVelocity = velocityY;
    }

    void UpdateSquareMoving(const GlobalPose& pose, uint32_t nowTick) {
        float distance = 0.0f;
        float speed = 0.0f;
        bool profileFinished = false;
        profile_.Sample(static_cast<float>(nowTick - stateStartTick_) * 0.001f,
                        distance, speed, profileFinished);

        const float heading = startPose_.yaw + static_cast<float>(squareSide_) * kHalfPi;
        const float directionX = std::cos(heading);
        const float directionY = std::sin(heading);
        const float targetX = segmentStart_.x + directionX * distance;
        const float targetY = segmentStart_.y + directionY * distance;
        const float allowedSpeed = speed > kSettleSpeed ? speed : kSettleSpeed;

        command_.targetYaw = heading;
        SetTrackingVelocity(pose, targetX, targetY, directionX * speed, directionY * speed, allowedSpeed);

        const float endpointX = segmentStart_.x + directionX;
        const float endpointY = segmentStart_.y + directionY;
        if (profileFinished && Distance(pose, endpointX, endpointY) < kPositionTolerance) {
            segmentStart_.x = endpointX;
            segmentStart_.y = endpointY;
            state_ = State::SquareTurning;
            stateStartTick_ = nowTick;
            command_.globalXVelocity = 0.0f;
            command_.globalYVelocity = 0.0f;
            command_.targetYaw = heading + kHalfPi;
        }
    }

    void UpdateSquareTurning(const GlobalPose& pose, uint32_t nowTick) {
        command_.globalXVelocity = 0.0f;
        command_.globalYVelocity = 0.0f;
        command_.targetYaw = startPose_.yaw + static_cast<float>(squareSide_ + 1) * kHalfPi;

        if (std::fabs(NormalizeAngle(command_.targetYaw - pose.yaw)) >= kYawTolerance) {
            return;
        }

        ++squareSide_;
        if (squareSide_ >= 4) {
            state_ = State::Finished;
            return;
        }

        profile_.Reset(1.0f);
        state_ = State::SquareMoving;
        stateStartTick_ = nowTick;
    }

    void UpdateCircleMoving(const GlobalPose& pose, uint32_t nowTick) {
        float arcLength = 0.0f;
        float speed = 0.0f;
        bool profileFinished = false;
        profile_.Sample(static_cast<float>(nowTick - stateStartTick_) * 0.001f,
                        arcLength, speed, profileFinished);

        constexpr float kRadius = 0.5f;
        const float theta = startPose_.yaw - kHalfPi + arcLength / kRadius;
        const float targetX = circleCenterX_ + kRadius * std::cos(theta);
        const float targetY = circleCenterY_ + kRadius * std::sin(theta);
        const float tangentX = -std::sin(theta);
        const float tangentY = std::cos(theta);
        const float allowedSpeed = speed > kSettleSpeed ? speed : kSettleSpeed;

        command_.targetYaw = startPose_.yaw;
        SetTrackingVelocity(pose, targetX, targetY, tangentX * speed, tangentY * speed, allowedSpeed);

        if (profileFinished && Distance(pose, startPose_.x, startPose_.y) < kPositionTolerance) {
            state_ = State::Finished;
            command_.globalXVelocity = 0.0f;
            command_.globalYVelocity = 0.0f;
        }
    }

    TrajectoryType type_ = TrajectoryType::Square;
    State state_ = State::Idle;
    uint8_t squareSide_ = 0;
    uint32_t stateStartTick_ = 0;
    float circleCenterX_ = 0.0f;
    float circleCenterY_ = 0.0f;
    GlobalPose startPose_{};
    GlobalPose segmentStart_{};
    TrapezoidalProfile profile_{};
    TrajectoryCommand command_{};
};

} // namespace

void TaskTest() {
    camYawAngle += static_cast<float>(v5streamer.joystickData.camYaw) * 0.01f;
    camPitchAngle += static_cast<float>(v5streamer.joystickData.camPitch) * 0.01f;
    Clamp(camYawAngle, -40.f, 40.f);
    Clamp(camPitchAngle, -30.f, 30.f);


    // 自动轨迹与键盘控制共用同一套归一化操控接口和 IMU 航向内环。
    // enablePathTracking 保持为 0；全局 AprilTag 位姿不参与 A 板控制切换。
    sub->Command(v5streamer.joystickData.yawRate,
                 v5streamer.joystickData.forwardSpeed,
                 v5streamer.joystickData.leftRightSpeed,
                 v5streamer.joystickData.downSpeed,
                 v5streamer.joystickData.upSpeed,
                 v5streamer.joystickData.startButton);
    // static uint8_t lastState = 0;
    // if (v5streamer.joystickData.fillLight) {
    //     static bool camLightState = false;
    //     if(lastState != v5streamer.joystickData.fillLight) {
    //         camLightState = !camLightState;
    //     }
    //     SUBLAB_FillLight<L1>::GetInstance().SetBrightness(camLightState ? 0.5f : 0.0f);
    //     SUBLAB_FillLight<L2>::GetInstance().SetBrightness(camLightState ? 0.5f : 0.0f);
    //     SUBLAB_FillLight<L3>::GetInstance().SetBrightness(camLightState ? 0.5f : 0.0f);
    // }
    // lastState = v5streamer.joystickData.fillLight;
}
TASK_EXPORT(TaskTest);
