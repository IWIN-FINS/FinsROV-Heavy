/*******************************************************************************
* Copyright (c) 2025.
* IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
* All rights reserved.
******************************************************************************/

#ifndef ATTITUDE_CONVERTER_H
#define ATTITUDE_CONVERTER_H

#include "Matrix/matrix.h"
#include <cmath>

class AttitudeConverter {
public:
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
    static void quatToEuler(float q0, float q1, float q2, float q3, 
                           float& roll, float& pitch, float& yaw);

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
    static void eulerToQuat(float roll, float pitch, float yaw,
                           float& q0, float& q1, float& q2, float& q3);

    /**
     * @brief 四元数转旋转矩阵
     * @param q0 四元数实部
     * @param q1 四元数虚部x
     * @param q2 四元数虚部y
     * @param q3 四元数虚部z
     * @return 3x3旋转矩阵
     */
    static Matrixf<3, 3> quatToMatrix(float q0, float q1, float q2, float q3);

    /**
     * @brief 旋转矩阵转四元数
     * @param rotation 3x3旋转矩阵
     * @param q0 四元数实部
     * @param q1 四元数虚部x
     * @param q2 四元数虚部y
     * @param q3 四元数虚部z
     */
    static void matrixToQuat(Matrixf<3, 3>& rotation,
                            float& q0, float& q1, float& q2, float& q3);

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
    static void quatToAxisAngle(float q0, float q1, float q2, float q3,
                               float& axis_x, float& axis_y, float& axis_z, float& angle);

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
    static void axisAngleToQuat(float axis_x, float axis_y, float axis_z, float angle,
                               float& q0, float& q1, float& q2, float& q3);
    
    /**
     * @brief 旋转矩阵转欧拉角 (东(X)--北(Y)--天(Z)--321顺序)
     * @param rotation 3x3旋转矩阵
     * @param roll 绕X轴旋转角度 (东)
     * @param pitch 绕Y轴旋转角度 (北)
     * @param yaw 绕Z轴旋转角度 (天)
     */
    static void matrixToEuler(Matrixf<3, 3>& rotation,
                             float& roll, float& pitch, float& yaw);
    
    /**
     * @brief 欧拉角转旋转矩阵 (东(X)--北(Y)--天(Z)--321顺序)
     * @param roll 绕X轴旋转角度 (东)
     * @param pitch 绕Y轴旋转角度 (北)
     * @param yaw 绕Z轴旋转角度 (天)
     * @return 3x3旋转矩阵
     */
    static Matrixf<3, 3> eulerToMatrix(float roll, float pitch, float yaw);
    
    /**
     * @brief 轴角转旋转矩阵
     * @param axis_x 旋转轴x分量
     * @param axis_y 旋转轴y分量
     * @param axis_z 旋转轴z分量
     * @param angle 旋转角度(弧度)
     * @return 3x3旋转矩阵
     */
    static Matrixf<3, 3> axisAngleToMatrix(float axis_x, float axis_y, float axis_z, float angle);
    
    /**
     * @brief 旋转矩阵转轴角
     * @param rotation 3x3旋转矩阵
     * @param axis_x 旋转轴x分量
     * @param axis_y 旋转轴y分量
     * @param axis_z 旋转轴z分量
     * @param angle 旋转角度(弧度)
     */
    static void matrixToAxisAngle(Matrixf<3, 3>& rotation,
                                 float& axis_x, float& axis_y, float& axis_z, float& angle);
};

#endif // ATTITUDE_CONVERTER_H