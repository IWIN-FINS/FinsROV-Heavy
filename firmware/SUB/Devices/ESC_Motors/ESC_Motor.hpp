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

    virtual void Set3DMode(bool enable) {}

    virtual void EnableMotor() {}

    virtual void DisableMotor() {}

protected:
    float rpm_ = 0.0f;
    float targetThrottle_ = 0.0f;
};

#endif // ESC_MOTOR_HPP
