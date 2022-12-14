#pragma once

#include <Arduino.h>
#include <Ticker.h>

#define BEEP_PIN 15


enum class BeepStatus : uint8_t
{
    On,
    Drip,
    Off,
};

class Beep
{
private:
    Ticker ticker;
    void BeepTask();

public:
    Beep();
    void Init();
    void SetStatus(BeepStatus status);
};
