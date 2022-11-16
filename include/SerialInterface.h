#pragma once

#include <Arduino.h>
#include <Ticker.h>
#include <RingBuf.h>
#include "Protocals.h"


class SerialInterface
{
private:
    Ticker ticker;
    RingBuf<uint8_t, 128> buffer;
    uint8_t currentBuf[128];
    bool halfReceived;
    void SerialTask();

public:
    SerialInterface();
    void Init();
};
