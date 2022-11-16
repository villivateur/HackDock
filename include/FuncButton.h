#pragma once

#include <Arduino.h>
#include <Ticker.h>

class FuncButton
{
private:
    Ticker scanner;
    uint32_t lastPressTimeMs;
    void Scan();

public:
    FuncButton();
    void Init();
    uint32_t MsSinceLastPress();
};
