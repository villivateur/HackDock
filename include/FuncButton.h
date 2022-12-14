#pragma once

#include <Arduino.h>
#include <Ticker.h>

class FuncButton
{
private:
    Ticker scanner;
    Ticker trigger;
    uint32_t lastPressTimeMs;
    void Scan();
    void Task();

public:
    FuncButton();
    void Init();
    uint32_t MsSinceLastPress();
};
