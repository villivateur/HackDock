#include <Arduino.h>
#include <Ticker.h>

class FuncButton
{
private:
    Ticker scanner;
    uint32_t lastPressTimeMs;

public:
    FuncButton();
    uint32_t MsSinceLastPress();
};
