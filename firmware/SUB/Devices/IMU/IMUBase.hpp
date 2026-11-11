/*******************************************************************************
* Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef IMU_BASE_FINEMOTE
#define IMU_BASE_FINEMOTE
#include "DeviceBase.h"
#include <array>
#include "AttitudeConverter.h"

class IMUBase : public DeviceBase
{
protected:
    bool isDataGet = false;

    Matrixf<3, 3> rotationOffset {-1, 0, 0, 0, -1, 0, 0, 0, 1}; // IMU安装位置180度旋转

    Matrixf<3, 3> rotationMatrix = matrixf::eye<3,3>();

    struct Accel {
        float ax = 0;
        float ay = 0;
        float az = 0;
    } accel;

    struct AngleRate {
        float wx = 0;
        float wy = 0;
        float wz = 0;
    } angleRate;
    // 欧拉角旋转顺序为东(X)--北(Y)--天(Z)--321(先转Z轴，再转Y轴，最后转 x轴)
    struct Euler{
        float pitch = 0;
        float roll = 0;
        float yaw = 0;
    } euler;

    struct Quat {
        float q0 = 0;
        float q1 = 0;
        float q2 = 0;
        float q3 = 0;
    } quat;

    struct AxisAngle {
        float axis_x = 0;     // 旋转轴 x 分量
        float axis_y = 0;     // 旋转轴 y 分量
        float axis_z = 0;     // 旋转轴 z 分量
        float angle = 0;      // 旋转角度(弧度)
    } axisAngle;

public:
    const Accel &getAccel() const { return accel; }
    const AngleRate &getAngleRate() const { return angleRate; }
    const Euler &getEuler() const { return euler; }
    const Quat &getQuat() const { return quat; }

    void UpdateAxisAngle() {
        AttitudeConverter::quatToAxisAngle(quat.q0, quat.q1, quat.q2, quat.q3,axisAngle.axis_x, axisAngle.axis_y, axisAngle.axis_z, axisAngle.angle);
    }

    bool IsDataGet() {
        return isDataGet;
    }

    std::array<float, 3> getAccelArray() const {
        std::array<float, 3> out{accel.ax, accel.ay, accel.az};
        return out;
    }
    std::array<float, 3> getAngleRateArray() const {
        std::array<float, 3> out{angleRate.wx, angleRate.wy, angleRate.wz};
        return out;
    }
    std::array<float, 3> getEulerArray() const {
        std::array<float, 3> out{euler.roll, euler.pitch, euler.yaw};
        return out;
    }
    std::array<float, 4> getQuatArray() const {
        std::array<float, 4> out{quat.q0, quat.q1, quat.q2, quat.q3};
        return out;
    }
};

#endif