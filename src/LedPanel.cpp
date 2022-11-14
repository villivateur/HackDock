#include "LedPanel.h"

LedPanel::LedPanel()
{
    pinMode(LED_FUN_0_PIN, OUTPUT);
    digitalWrite(LED_FUN_0_PIN, HIGH);
    pinMode(LED_FUN_1_PIN, OUTPUT);
    digitalWrite(LED_FUN_1_PIN, HIGH);
}

static void Led0BlinkTask()
{
    digitalWrite(LED_FUN_0_PIN, !digitalRead(LED_FUN_0_PIN));     // set pin to the opposite state
}

static void Led1BlinkTask()
{
    digitalWrite(LED_FUN_1_PIN, !digitalRead(LED_FUN_1_PIN));     // set pin to the opposite state
}

void LedPanel::SetBlinkRate(Ticker* flipper, std::function<void(void)> func, LedBlinkRate rate)
{
    switch (rate)
    {
    case LedBlinkRate::Rate8Hz:
        flipper->attach(0.0625, func);        
        break;
    case LedBlinkRate::Rate2Hz:
        flipper->attach(0.25, func);        
        break;
    case LedBlinkRate::Rate0_5Hz:
        flipper->attach(1.0, func);        
        break;
    default:
        break;
    }
}

void LedPanel::SetLed(uint8_t ledNum, LedBlinkRate rate)
{
    switch (ledNum)
    {
    case 0:
        switch (rate)
        {
        case LedBlinkRate::RateAlwaysOn:
            ledFlipper_0.detach();
            digitalWrite(LED_FUN_0_PIN, LOW);
            break;
        case LedBlinkRate::RateAlwaysOff:
            ledFlipper_0.detach();
            digitalWrite(LED_FUN_0_PIN, HIGH);
            break;
        default:
            SetBlinkRate(&ledFlipper_0, Led0BlinkTask, rate);
            break;
        }
        break;
    case 1:
        switch (rate)
        {
        case LedBlinkRate::RateAlwaysOn:
            ledFlipper_1.detach();
            digitalWrite(LED_FUN_1_PIN, LOW);
            break;
        case LedBlinkRate::RateAlwaysOff:
            ledFlipper_1.detach();
            digitalWrite(LED_FUN_1_PIN, HIGH);
            break;
        default:
            SetBlinkRate(&ledFlipper_1, Led1BlinkTask, rate);
            break;
        }
        break;
    default:
        break;
    }
}