#pragma once

#include <Arduino.h>
#include <Ticker.h>
#include <RingBuf.h>
#include "Protocals.h"


class SerialInterface
{
private:
    Ticker ticker;
    RingBuf<uint8_t, 128> ringBuffer;
    String cmdLine;
    bool halfReceived;
    void SerialTask();
    void CmdHandler(String cmdLine);
    void ParseCmd(String cmd);

public:
    SerialInterface();
    void Init();
};
