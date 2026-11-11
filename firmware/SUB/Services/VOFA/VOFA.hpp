/*******************************************************************************
 * Copyright (c) 2026.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef VOFA_HPP
#define VOFA_HPP

#include "Bus/UART_Base.hpp"
#include "DeviceBase.h"

#define DATA_LENGTH 10
#define MESSAGE_LENGTH (4 * DATA_LENGTH + 4)


template <uint8_t UART_ID>
class VOFA : public DeviceBase {
public:
    static VOFA &GetInstance() {
        static VOFA instance;
        return instance;
    }

    VOFA(const VOFA &) = delete;
    VOFA &operator=(const VOFA &) = delete;

    void SetData(float value, size_t index) {
        if (index < DATA_LENGTH) {
            message.data[index] = value;
        }
    }

    void Handle() final {
        std::memcpy(txBuffer, &message, MESSAGE_LENGTH);
        UART_Base<UART_ID>::GetInstance().Transmit(txBuffer, MESSAGE_LENGTH);
    }

private:
    VOFA() {
        this->SetDivisionFactor(10);
    }

    struct justFloat {
        float data[DATA_LENGTH]{};
        uint8_t tail[4]{0x00, 0x00, 0x80, 0x7f};
    } message __packed;
    static constexpr size_t tailSize = 4;
    uint8_t txBuffer[MESSAGE_LENGTH]{};
};

#endif // VOFA_HPP
