#include "FuncButton.h"

#define FUNC_BTN 0
#define PRESSED_STATUS LOW

uint32_t* lastPressTimeMsPtr = NULL;

static void Scan()
{
    if (digitalRead(FUNC_BTN) == PRESSED_STATUS) {
        *lastPressTimeMsPtr = millis();
    }
}

uint32_t FuncButton::MsSinceLastPress()
{
    return millis() - lastPressTimeMs;
}

FuncButton::FuncButton()
{
    lastPressTimeMsPtr = &lastPressTimeMs;
    pinMode(FUNC_BTN, INPUT);    
    scanner.attach(0.001, Scan);
}
