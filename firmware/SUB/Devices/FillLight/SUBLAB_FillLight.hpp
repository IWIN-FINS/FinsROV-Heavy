/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef FINEMOTE_SUBLAB_FILLLIGHT_HPP
#define FINEMOTE_SUBLAB_FILLLIGHT_HPP

#include "Bus/PWM_Base.hpp"
#include <cmath>

#define MIN_US (1100.0f)
#define MAX_US (1900.0f)
#define PERIOD_US (20000.0f)

template <size_t ID>
class SUBLAB_FillLight {
public:
    static SUBLAB_FillLight &GetInstance() {
        static SUBLAB_FillLight instance;
        return instance;
    }

    // 输入归一化亮度 0.0 - 1.0，映射到脉宽 1100us - 1900us，并设置 PWM 占空比
    void SetBrightness(float brightness) {
        if (std::isnan(brightness)) // NaN guard
            brightness = 0.0f;
        if (brightness < 0.0f)
            brightness = 0.0f;
        else if (brightness > 1.0f)
            brightness = 1.0f;

        float pulse_us = MIN_US + brightness * (MAX_US - MIN_US);
        float duty = pulse_us / PERIOD_US;

        PWM_Base<ID>::GetInstance().SetDutyCycle(duty);
    }

    SUBLAB_FillLight(const SUBLAB_FillLight &) = delete;
    SUBLAB_FillLight &operator=(const SUBLAB_FillLight &) = delete;

private:
    SUBLAB_FillLight() {
        PWM_Base<ID>::GetInstance().SetFrequency(50);
        PWM_Base<ID>::GetInstance().SetDutyCycle(0.0f);
    }

    ~SUBLAB_FillLight() = default;
};


#endif //FINEMOTE_SUBLAB_FILLLIGHT_HPP
