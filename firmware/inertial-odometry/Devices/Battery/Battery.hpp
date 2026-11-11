/******************************************************************************
 * Copyright (c) 2026.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 *******************************************************************/

#ifndef BATTERY_HPP
#define BATTERY_HPP

#include "Bus/CAN_Base.hpp"
#include "Battery/BatteryBase.hpp"

#define CURRENT_OFFSET 30000.0f
#define BOARD_TEMPERATURE_OFFSET 40.0f
#define SINGLE_TEMPERATURE_OFFSET 40.0f

#define VOLTAGE_SCALE 0.1f
#define CURRENT_SCALE 0.1f
#define SOC_SCALE 0.1f
#define BOARD_TEMPERATURE_SCALE 1.0f
#define SINGLE_TEMPERATURE_SCALE 1.0f

template<size_t busID>
class Battery : public BatteryBase
{
	public:
		Battery(uint8_t ID)
				: canAgent1(0x04028000 | ID), canAgent2(0x04038000 | ID), canAgent3(0x04058000 | ID)
		{
			this->SetDivisionFactor(200);
		}

		void Handle() override
		{
			memcpy(data1, canAgent1.rxbuf, 8);
			memcpy(data2, canAgent2.rxbuf, 8);
			memcpy(data3, canAgent3.rxbuf, 8);

			voltage = (data1[0] << 8 | data1[1]) * VOLTAGE_SCALE;
			current = ((data1[2] << 8 | data1[3]) - CURRENT_OFFSET) * CURRENT_SCALE;
			soc = (data1[4] << 8 | data1[5]) * SOC_SCALE;

			board_temperature = (data2[5] - BOARD_TEMPERATURE_OFFSET) * BOARD_TEMPERATURE_SCALE;

			single_temperature_max = (data3[0] - SINGLE_TEMPERATURE_OFFSET) * SINGLE_TEMPERATURE_SCALE;

			if(count >= 10)
			{
				canAgent4[0] = 0x00;
				canAgent4[1] = 0x00;
				canAgent4[2] = 0x00;
				canAgent4[3] = 0x00;
				canAgent4[4] = 0x00;
				canAgent4[5] = 0x00;
				canAgent4[6] = 0x00;
				canAgent4[7] = 0x00;
				canAgent4.Transmit(0x0400FF80, CAN_ID_EXT | CAN_RTR_DATA);
				count = 0;
			}

			count++;
		}

		float GetVoltage() const { return voltage; }
		float GetCurrent() const { return current; }
		float GetSingleTemperatureMax() const { return single_temperature_max; }
		float GetBoardTemperature() const { return board_temperature; }
		float GetSOC() const { return soc; }

	private:
		CAN_Agent<busID> canAgent1;
		CAN_Agent<busID> canAgent2;
		CAN_Agent<busID> canAgent3;
		CAN_Agent<busID> canAgent4{0x0400FF80};

		uint8_t data1[8]{};
		uint8_t data2[8]{};
		uint8_t data3[8]{};

		float voltage = 0.0f;
		float current = 0.0f;
		float single_temperature_max = 0.0f;
		float board_temperature = 0.0f;
		float soc = 0.0f;

		uint8_t count = 0;
};

#endif
