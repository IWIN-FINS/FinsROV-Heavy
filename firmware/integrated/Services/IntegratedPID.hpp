// SPDX-License-Identifier: MPL-2.0
#pragma once
#include "../../inertial-odometry/Algorithms/Control/PID.hpp"
// Same discrete gains as the inherited PID, with explicit lifecycle reset.
class IntegratedPID : public ControllerBase {
public:
    explicit IntegratedPID(const PID_Param_t& value):params(value) {}
    const float& Calc() override {
        const float error=*targetPtr-*feedbackPtr;
        integral+=error;Clamp(integral,-params.iMax,params.iMax);
        output=params.kp*error+params.ki*integral+params.kd*(error-previous);
        previous=error;Clamp(output,-params.outputMax,params.outputMax);return output;
    }
    void Reset() {integral=previous=output=0;}
private:
    PID_Param_t params;
    float integral=0,previous=0;
};
