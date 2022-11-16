#include "FuncButton.h"
#include "Beep.h"

extern Beep beep;

#define FUNC_BTN 0
#define PRESSED_STATUS LOW
#define BUTTON_SCAN_PERIOD 1
#define BUTTON_TASK_PEROID 100


FuncButton::FuncButton()
{
    pinMode(FUNC_BTN, INPUT);
    lastPressTimeMs = UINT32_MAX;
}

void FuncButton::Init()
{
    scanner.attach_ms(BUTTON_SCAN_PERIOD, std::bind(&FuncButton::Scan, this));
    trigger.attach_ms(BUTTON_TASK_PEROID, std::bind(&FuncButton::Task, this));
}

void FuncButton::Scan()
{
    if (digitalRead(FUNC_BTN) == PRESSED_STATUS) {
        lastPressTimeMs = millis();
    }
}

void FuncButton::Task()
{
    if (MsSinceLastPress() < BUTTON_TASK_PEROID) {
        beep.SetStatus(BeepStatus::Off);
    }
}

uint32_t FuncButton::MsSinceLastPress()
{
    return millis() - lastPressTimeMs;
}
