/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef ESC_MOTOR_HPP
#define ESC_MOTOR_HPP

#include "../DeviceBase.h"

class ESC_Motor : public DeviceBase {
public:
    ESC_Motor() noexcept = default;
    ~ESC_Motor() noexcept override = default;

    void SetThrottle(float targetThrottle) {
        targetThrottle_ = targetThrottle;
    }

    float GetRPM() const {
        return rpm_;
    }

    /*** 当前下发给电调的油门指令（SetThrottle写入值），用于遥测回传 ***/
    float GetThrottle() const {
        return targetThrottle_;
    }

    int16_t GetIntRpm() const {
        return intRpm;
    }

    virtual void Set3DMode(bool enable) {}

    virtual void EnableMotor() {}

    virtual void DisableMotor() {}

protected:
    float rpm_ = 0.0f;
    int16_t intRpm = 0;
    float targetThrottle_ = 0.0f;
};

#endif // ESC_MOTOR_HPP
