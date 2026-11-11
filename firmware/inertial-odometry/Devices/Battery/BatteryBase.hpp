/******************************************************************************
 * Copyright (c) 2026.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ***************************************************************/

#ifndef BATTERYBASE_HPP
#define BATTERYBASE_HPP

#include "DeviceBase.h"

class BatteryBase : public DeviceBase
{
public:
	virtual float GetVoltage() const = 0;
	virtual float GetCurrent() const = 0;
	virtual float GetSOC() const = 0;
	virtual float GetSingleTemperatureMax() const = 0;
	virtual float GetBoardTemperature() const = 0;
};

#endif
