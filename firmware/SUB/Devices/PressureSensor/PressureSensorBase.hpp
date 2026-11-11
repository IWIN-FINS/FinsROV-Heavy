/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef PRESSURESENSOR_HPP
#define PRESSURESENSOR_HPP


#include "DeviceBase.h"

class PressureSensorBase : public DeviceBase {
public:
    float GetPressure() const {
        return pressure;
    }

    float GetFrequency() const {
        return frequency;
    }

protected:
    float pressure = 0.0f; //单位:Pa
    float frequency = 0.0f; //采样频率,单位:Hz
};


#endif //PRESSURESENSOR_HPP
