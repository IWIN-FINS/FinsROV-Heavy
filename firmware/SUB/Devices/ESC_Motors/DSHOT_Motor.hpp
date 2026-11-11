/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef DSHOT_MOTOR_HPP
#define DSHOT_MOTOR_HPP

#include "ESC_Motors/ESC_Motor.hpp"
#include "Bus/DSHOT.hpp"
#include <cstdint>

template <uint16_t ID>
class DSHOT_Motor : public ESC_Motor {
public:
    static DSHOT_Motor& GetInstance() {
        static DSHOT_Motor instance;
        return instance;
    }

    DSHOT_Motor(const DSHOT_Motor&) = delete;
    DSHOT_Motor& operator=(const DSHOT_Motor&) = delete;

    ~DSHOT_Motor() noexcept override = default;

    void Set3DMode(bool enable) override {
        DSHOT_PIN<ID>::GetInstance().Set3DMode(enable);
    }

    void EnableMotor() override {
        DSHOT_PIN<ID>::GetInstance().EnableMotor();
    }

    void DisableMotor() override {
        DSHOT_PIN<ID>::GetInstance().DisableMotor();
    }

    void Handle() override {
        rpm_ = DSHOT_PIN<ID>::GetInstance().GetRPM();
        DSHOT_PIN<ID>::GetInstance().SetTargetThrottle(targetThrottle_);
    }

private:
    DSHOT_Motor() {
        DSHOT_PIN<ID>::GetInstance().DisableMotor();
        DSHOT_PIN<ID>::GetInstance().Set3DMode(true);
        DSHOT_PIN<ID>::GetInstance().SetTelemetry(true);
    }
};

#endif //DSHOT_MOTOR_HPP
