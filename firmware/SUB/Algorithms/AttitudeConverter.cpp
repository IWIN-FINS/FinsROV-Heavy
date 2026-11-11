/*******************************************************************************
* Copyright (c) 2025.
* IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
* All rights reserved.
******************************************************************************/

#include "AttitudeConverter.h"
#include <cmath>
#include <algorithm>

/**
 * @brief 四元数转欧拉角 (东(X)--北(Y)--天(Z)--321顺序)
 * @param q0 四元数实部
 * @param q1 四元数虚部x
 * @param q2 四元数虚部y
 * @param q3 四元数虚部z
 * @param roll 绕X轴旋转角度 (东)
 * @param pitch 绕Y轴旋转角度 (北)
 * @param yaw 绕Z轴旋转角度 (天)
 */
void AttitudeConverter::quatToEuler(float q0, float q1, float q2, float q3, 
                                   float& roll, float& pitch, float& yaw) {
    // Roll (X轴旋转)
    float sinr_cosp = 2.0f * (q0 * q1 + q2 * q3);
    float cosr_cosp = 1.0f - 2.0f * (q1 * q1 + q2 * q2);
    roll = atan2f(sinr_cosp, cosr_cosp);

    // Pitch (Y轴旋转)
    float sinp = 2.0f * (q0 * q2 - q3 * q1);
    if (fabsf(sinp) >= 1.0f) {
        pitch = copysignf(PI / 2.0f, sinp); // 使用90度作为阈值
    } else {
        pitch = asinf(sinp);
    }

    // Yaw (Z轴旋转)
    float siny_cosp = 2.0f * (q0 * q3 + q1 * q2);
    float cosy_cosp = 1.0f - 2.0f * (q2 * q2 + q3 * q3);
    yaw = atan2f(siny_cosp, cosy_cosp);
}

/**
 * @brief 欧拉角转四元数 (东(X)--北(Y)--天(Z)--321顺序)
 * @param roll 绕X轴旋转角度 (东)
 * @param pitch 绕Y轴旋转角度 (北)
 * @param yaw 绕Z轴旋转角度 (天)
 * @param q0 四元数实部
 * @param q1 四元数虚部x
 * @param q2 四元数虚部y
 * @param q3 四元数虚部z
 */
void AttitudeConverter::eulerToQuat(float roll, float pitch, float yaw,
                                   float& q0, float& q1, float& q2, float& q3) {
    // 计算半角
    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);
    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);
    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);

    q0 = cr * cp * cy + sr * sp * sy;
    q1 = sr * cp * cy - cr * sp * sy;
    q2 = cr * sp * cy + sr * cp * sy;
    q3 = cr * cp * sy - sr * sp * cy;
}

/**
 * @brief 四元数转旋转矩阵
 * @param q0 四元数实部
 * @param q1 四元数虚部x
 * @param q2 四元数虚部y
 * @param q3 四元数虚部z
 * @return 3x3旋转矩阵
 */
Matrixf<3, 3> AttitudeConverter::quatToMatrix(float q0, float q1, float q2, float q3) {
    float data[9];
    
    // 第一行
    data[0] = 1.0f - 2.0f * (q2 * q2 + q3 * q3);
    data[1] = 2.0f * (q1 * q2 - q0 * q3);
    data[2] = 2.0f * (q1 * q3 + q0 * q2);
    
    // 第二行
    data[3] = 2.0f * (q1 * q2 + q0 * q3);
    data[4] = 1.0f - 2.0f * (q1 * q1 + q3 * q3);
    data[5] = 2.0f * (q2 * q3 - q0 * q1);
    
    // 第三行
    data[6] = 2.0f * (q1 * q3 - q0 * q2);
    data[7] = 2.0f * (q2 * q3 + q0 * q1);
    data[8] = 1.0f - 2.0f * (q1 * q1 + q2 * q2);
    
    return Matrixf<3, 3>(data);
}

/**
 * @brief 旋转矩阵转四元数
 * @param rotation 3x3旋转矩阵
 * @param q0 四元数实部
 * @param q1 四元数虚部x
 * @param q2 四元数虚部y
 * @param q3 四元数虚部z
 */
void AttitudeConverter::matrixToQuat(Matrixf<3, 3>& rotation,
                                    float& q0, float& q1, float& q2, float& q3) {
    float trace = rotation[0][0] + rotation[1][1] + rotation[2][2];
    
    if (trace > 0) {
        float s = sqrtf(trace + 1.0f) * 2.0f; // s = 4 * q0
        q0 = 0.25f * s;
        q1 = (rotation[2][1] - rotation[1][2]) / s;
        q2 = (rotation[0][2] - rotation[2][0]) / s;
        q3 = (rotation[1][0] - rotation[0][1]) / s;
    } else if ((rotation[0][0] > rotation[1][1]) && (rotation[0][0] > rotation[2][2])) {
        float s = sqrtf(1.0f + rotation[0][0] - rotation[1][1] - rotation[2][2]) * 2.0f; // s = 4 * q1
        q0 = (rotation[2][1] - rotation[1][2]) / s;
        q1 = 0.25f * s;
        q2 = (rotation[0][1] + rotation[1][0]) / s;
        q3 = (rotation[0][2] + rotation[2][0]) / s;
    } else if (rotation[1][1] > rotation[2][2]) {
        float s = sqrtf(1.0f + rotation[1][1] - rotation[0][0] - rotation[2][2]) * 2.0f; // s = 4 * q2
        q0 = (rotation[0][2] - rotation[2][0]) / s;
        q1 = (rotation[0][1] + rotation[1][0]) / s;
        q2 = 0.25f * s;
        q3 = (rotation[1][2] + rotation[2][1]) / s;
    } else {
        float s = sqrtf(1.0f + rotation[2][2] - rotation[0][0] - rotation[1][1]) * 2.0f; // s = 4 * q3
        q0 = (rotation[1][0] - rotation[0][1]) / s;
        q1 = (rotation[0][2] + rotation[2][0]) / s;
        q2 = (rotation[1][2] + rotation[2][1]) / s;
        q3 = 0.25f * s;
    }
    
    // 标准化四元数
    float norm = sqrtf(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    if (norm > 1e-12f) {
        q0 /= norm;
        q1 /= norm;
        q2 /= norm;
        q3 /= norm;
    }
}

/**
 * @brief 四元数转轴角
 * @param q0 四元数实部
 * @param q1 四元数虚部x
 * @param q2 四元数虚部y
 * @param q3 四元数虚部z
 * @param axis_x 旋转轴x分量
 * @param axis_y 旋转轴y分量
 * @param axis_z 旋转轴z分量
 * @param angle 旋转角度(弧度)
 */
void AttitudeConverter::quatToAxisAngle(float q0, float q1, float q2, float q3,
                                       float& axis_x, float& axis_y, float& axis_z, float& angle) {
    // 计算旋转角度
    angle = 2.0f * acosf(q0);  // angle = 2 * arccos(q0)
    
    // 计算旋转轴
    float s = sqrtf(1.0f - q0 * q0); // s = sin(angle/2)
    
    if (s < 1e-6f) {  // 如果 s 接近 0，说明角度接近 0 或 2π
        // 此时可以选择任意轴，通常选择 z 轴
        axis_x = 0.0f;
        axis_y = 0.0f;
        axis_z = 1.0f;
    } else {
        // 标准情况: 轴向量 = (q1, q2, q3) / sin(angle/2)
        axis_x = q1 / s;
        axis_y = q2 / s;
        axis_z = q3 / s;
        
        // 标准化轴向量
        float norm = sqrtf(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
        if (norm > 1e-12f) {
            axis_x /= norm;
            axis_y /= norm;
            axis_z /= norm;
        }
    }
}

/**
 * @brief 轴角转四元数
 * @param axis_x 旋转轴x分量
 * @param axis_y 旋转轴y分量
 * @param axis_z 旋转轴z分量
 * @param angle 旋转角度(弧度)
 * @param q0 四元数实部
 * @param q1 四元数虚部x
 * @param q2 四元数虚部y
 * @param q3 四元数虚部z
 */
void AttitudeConverter::axisAngleToQuat(float axis_x, float axis_y, float axis_z, float angle,
                                       float& q0, float& q1, float& q2, float& q3) {
    // 计算半角
    float half_angle = angle * 0.5f;
    float sin_half_angle = sinf(half_angle);
    float cos_half_angle = cosf(half_angle);
    
    // 计算四元数
    q0 = cos_half_angle;
    q1 = axis_x * sin_half_angle;
    q2 = axis_y * sin_half_angle;
    q3 = axis_z * sin_half_angle;
    
    // 标准化四元数
    float norm = sqrtf(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    if (norm > 1e-12f) {
        q0 /= norm;
        q1 /= norm;
        q2 /= norm;
        q3 /= norm;
    }
}

/**
 * @brief 旋转矩阵转欧拉角 (东(X)--北(Y)--天(Z)--321顺序)
 * @param rotation 3x3旋转矩阵
 * @param roll 绕X轴旋转角度 (东)
 * @param pitch 绕Y轴旋转角度 (北)
 * @param yaw 绕Z轴旋转角度 (天)
 */
void AttitudeConverter::matrixToEuler(Matrixf<3, 3>& rotation,
                                     float& roll, float& pitch, float& yaw) {
    // 从矩阵元素计算欧拉角
    float sin_pitch = -rotation[2][0];
    
    if (fabsf(sin_pitch) >= 1.0f) {
        pitch = copysignf(PI / 2.0f, sin_pitch);
        roll = 0.0f;
        yaw = atan2f(-rotation[0][1], rotation[1][1]);
    } else {
        pitch = asinf(sin_pitch);
        roll = atan2f(rotation[2][1], rotation[2][2]);
        yaw = atan2f(rotation[1][0], rotation[0][0]);
    }
}

/**
 * @brief 欧拉角转旋转矩阵 (东(X)--北(Y)--天(Z)--321顺序)
 * @param roll 绕X轴旋转角度 (东)
 * @param pitch 绕Y轴旋转角度 (北)
 * @param yaw 绕Z轴旋转角度 (天)
 * @return 3x3旋转矩阵
 */
Matrixf<3, 3> AttitudeConverter::eulerToMatrix(float roll, float pitch, float yaw) {
    float cos_roll = cosf(roll);
    float sin_roll = sinf(roll);
    float cos_pitch = cosf(pitch);
    float sin_pitch = sinf(pitch);
    float cos_yaw = cosf(yaw);
    float sin_yaw = sinf(yaw);
    
    float data[9];
    
    // 第一行
    data[0] = cos_pitch * cos_yaw;
    data[1] = sin_roll * sin_pitch * cos_yaw - cos_roll * sin_yaw;
    data[2] = cos_roll * sin_pitch * cos_yaw + sin_roll * sin_yaw;
    
    // 第二行
    data[3] = cos_pitch * sin_yaw;
    data[4] = sin_roll * sin_pitch * sin_yaw + cos_roll * cos_yaw;
    data[5] = cos_roll * sin_pitch * sin_yaw - sin_roll * cos_yaw;
    
    // 第三行
    data[6] = -sin_pitch;
    data[7] = sin_roll * cos_pitch;
    data[8] = cos_roll * cos_pitch;
    
    return Matrixf<3, 3>(data);
}

/**
 * @brief 轴角转旋转矩阵
 * @param axis_x 旋转轴x分量
 * @param axis_y 旋转轴y分量
 * @param axis_z 旋转轴z分量
 * @param angle 旋转角度(弧度)
 * @return 3x3旋转矩阵
 */
Matrixf<3, 3> AttitudeConverter::axisAngleToMatrix(float axis_x, float axis_y, float axis_z, float angle) {
    // 确保轴是单位向量
    float norm = sqrtf(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
    float ux = axis_x, uy = axis_y, uz = axis_z;
    
    if (norm > 1e-12f) {
        ux /= norm;
        uy /= norm;
        uz /= norm;
    }
    
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    float one_minus_cos = 1.0f - cos_angle;
    
    float data[9];
    
    // 第一行
    data[0] = cos_angle + ux * ux * one_minus_cos;
    data[1] = ux * uy * one_minus_cos - uz * sin_angle;
    data[2] = ux * uz * one_minus_cos + uy * sin_angle;
    
    // 第二行
    data[3] = uy * ux * one_minus_cos + uz * sin_angle;
    data[4] = cos_angle + uy * uy * one_minus_cos;
    data[5] = uy * uz * one_minus_cos - ux * sin_angle;
    
    // 第三行
    data[6] = uz * ux * one_minus_cos - uy * sin_angle;
    data[7] = uz * uy * one_minus_cos + ux * sin_angle;
    data[8] = cos_angle + uz * uz * one_minus_cos;
    
    return Matrixf<3, 3>(data);
}

/**
 * @brief 旋转矩阵转轴角
 * @param rotation 3x3旋转矩阵
 * @param axis_x 旋转轴x分量
 * @param axis_y 旋转轴y分量
 * @param axis_z 旋转轴z分量
 * @param angle 旋转角度(弧度)
 */
void AttitudeConverter::matrixToAxisAngle(Matrixf<3, 3>& rotation,
                                         float& axis_x, float& axis_y, float& axis_z, float& angle) {
    // 计算旋转角度
    float trace = rotation[0][0] + rotation[1][1] + rotation[2][2];
    angle = acosf(fminf(fmaxf((trace - 1.0f) / 2.0f, -1.0f), 1.0f));
    
    // 计算旋转轴
    if (fabsf(angle) < 1e-6f) {
        // 角度接近0，轴可以是任意方向，这里选择z轴
        axis_x = 0.0f;
        axis_y = 0.0f;
        axis_z = 1.0f;
    } else if (fabsf(angle - PI) < 1e-6f) {
        // 角度接近π，需要特殊处理
        // 查找最大的对角线元素
        if (rotation[0][0] >= rotation[1][1] && rotation[0][0] >= rotation[2][2]) {
            float denominator = sqrtf(fmaxf(1.0f + rotation[0][0] - rotation[1][1] - rotation[2][2], 0.0f)) * 2.0f;
            axis_x = 0.5f * denominator;
            axis_y = (rotation[0][1] + rotation[1][0]) / denominator;
            axis_z = (rotation[0][2] + rotation[2][0]) / denominator;
        } else if (rotation[1][1] >= rotation[2][2]) {
            float denominator = sqrtf(fmaxf(1.0f - rotation[0][0] + rotation[1][1] - rotation[2][2], 0.0f)) * 2.0f;
            axis_x = (rotation[0][1] + rotation[1][0]) / denominator;
            axis_y = 0.5f * denominator;
            axis_z = (rotation[1][2] + rotation[2][1]) / denominator;
        } else {
            float denominator = sqrtf(fmaxf(1.0f - rotation[0][0] - rotation[1][1] + rotation[2][2], 0.0f)) * 2.0f;
            axis_x = (rotation[0][2] + rotation[2][0]) / denominator;
            axis_y = (rotation[1][2] + rotation[2][1]) / denominator;
            axis_z = 0.5f * denominator;
        }
    } else {
        // 标准情况
        axis_x = rotation[2][1] - rotation[1][2];
        axis_y = rotation[0][2] - rotation[2][0];
        axis_z = rotation[1][0] - rotation[0][1];
        
        // 标准化轴
        float norm = sqrtf(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
        if (norm > 1e-12f) {
            axis_x /= norm;
            axis_y /= norm;
            axis_z /= norm;
        }
    }
}
