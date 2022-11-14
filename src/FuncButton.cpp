#include "FuncButton.h"

#define FUNC_BTN 0
#define PRESSED_STATUS LOW


FuncButton::FuncButton()
{
    pinMode(FUNC_BTN, INPUT);    
    scanner.attach_ms(1, std::bind(&FuncButton::Scan, this));
}

void FuncButton::Scan()
{
    if (digitalRead(FUNC_BTN) == PRESSED_STATUS) {
        lastPressTimeMs = millis();
    }
}

uint32_t FuncButton::MsSinceLastPress()
{
    return millis() - lastPressTimeMs;
}
