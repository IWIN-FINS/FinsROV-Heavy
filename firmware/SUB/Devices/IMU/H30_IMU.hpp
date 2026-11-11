/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef H30_IMU_FINEMOTE
#define H30_IMU_FINEMOTE
#include "Bus/UART_Base.hpp"
#include "IMU/IMUBase.hpp"
#include "dsp/fast_math_functions.h"


class H30_IMU : public IMUBase {
public:
    void Decode(uint8_t *data, uint16_t length) {
        if (data[0] == 0x59 && data[1] == 0x53 && H30CheckSum(data + 2, length - 4) == (data[length - 2] << 8 | data[length - 1])) {
            uint8_t pEuler = 5;
            while (pEuler < length - 2) {
                switch (data[pEuler]) {
                case 0x10: // AccelDataId
                    DecodeAccel(data + pEuler + 2);
                    break;
                case 0x20: // AngleRateDataId
                    DecodeAngleRate(data + pEuler + 2);
                    break;
                case 0x40: // EulerDataId
                    // DecodeEuler(data + pEuler + 2);
                    break;
                case 0x41: // QuatDataId
                    DecodeQuat(data + pEuler + 2);
                    break;
                default:
                    break;
                }
                pEuler += data[pEuler + 1] + 2; // 调到下一段数据开头
            }
            UpdateAxisAngle();
            isDataGet = true;
        }
    }

    void Handle() final {}

private:
    void UpdateEuler(float q0, float q1, float q2, float q3) {
        float roll_,pitch_,yaw_;
        AttitudeConverter::quatToEuler(q0, q1, q2, q3, roll_, pitch_, yaw_);

        euler.roll = roll_;
        euler.pitch = pitch_;
        while (euler.yaw - yaw_ > 1.9 * PI)
        {
            yaw_ += 2*PI;
        }
        while (euler.yaw - yaw_ < -1.9 * PI)
        {
            yaw_ -= 2*PI;
        }
        euler.yaw = yaw_;
    }

    void DecodeEuler(uint8_t *data) {
        euler.pitch = static_cast<float>(data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24) * 0.000001 / 180.f * PI;
        euler.roll = static_cast<float>(data[4] | data[5] << 8 | data[6] << 16 | data[7] << 24) * 0.000001 / 180.f * PI;
        float yaw = static_cast<float>(data[8] | data[9] << 8 | data[10] << 16 | data[11] << 24) * 0.000001 / 180.f * PI;

        while (euler.yaw - yaw > 1.9 * PI) {
            yaw += 2 * PI;
        }
        while (euler.yaw - yaw < -1.9 * PI) {
            yaw -= 2 * PI;
        }
        euler.yaw = yaw;
    }

    void DecodeAngleRate(uint8_t *data) {
        float wx = static_cast<float>(data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24) * 0.000001f / 180.f * PI;
        float wy = static_cast<float>(data[4] | data[5] << 8 | data[6] << 16 | data[7] << 24) * 0.000001f / 180.f * PI;
        float wz = static_cast<float>(data[8] | data[9] << 8 | data[10] << 16 | data[11] << 24) * 0.000001f / 180.f * PI;
        Matrixf<3,1> angleRateMatrix{wx, wy, wz};

        angleRateMatrix = rotationOffset * angleRateMatrix;

        angleRate.wx = angleRateMatrix[0][0];
        angleRate.wy = angleRateMatrix[1][0];
        angleRate.wz = angleRateMatrix[2][0];

        // angleRate.wx = static_cast<float>(data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24) * 0.000001f / 180.f * PI;
        // angleRate.wy = static_cast<float>(data[4] | data[5] << 8 | data[6] << 16 | data[7] << 24) * 0.000001f / 180.f * PI;
        // angleRate.wz = static_cast<float>(data[8] | data[9] << 8 | data[10] << 16 | data[11] << 24) * 0.000001f / 180.f * PI;
    }

    void DecodeAccel(uint8_t *data) {
        accel.ax = static_cast<float>(data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24) * 0.000001f;
        accel.ay = static_cast<float>(data[4] | data[5] << 8 | data[6] << 16 | data[7] << 24) * 0.000001f;
        accel.az = static_cast<float>(data[8] | data[9] << 8 | data[10] << 16 | data[11] << 24) * 0.000001f;
    }

    void DecodeQuat(uint8_t *data) {
        float q0 = static_cast<float>(data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24) * 0.000001f;
        float q1 = static_cast<float>(data[4] | data[5] << 8 | data[6] << 16 | data[7] << 24) * 0.000001f;
        float q2 = static_cast<float>(data[8] | data[9] << 8 | data[10] << 16 | data[11] << 24) * 0.000001f;
        float q3 = static_cast<float>(data[12] | data[13] << 8 | data[14] << 16 | data[15] << 24) * 0.000001f;

        Matrixf<3,3> rotMat = AttitudeConverter::quatToMatrix(q0, q1, q2, q3);
        rotMat = rotMat * rotationOffset;

        rotationMatrix = rotMat;//更新旋转矩阵
        AttitudeConverter::matrixToQuat(rotMat, quat.q0, quat.q1, quat.q2, quat.q3);//更新四元数
        UpdateEuler(quat.q0, quat.q1, quat.q2, quat.q3);//更新欧拉角
    }

    uint16_t H30CheckSum(uint8_t *data, uint16_t len) {
        uint8_t ck1 = 0, ck2 = 0;
        for (uint16_t i = 0; i < len; i++) {
            ck1 += data[i];
            ck2 += ck1;
        }
        uint16_t ck = (ck1 << 8) | ck2;
        return ck;
    }
};

#endif
