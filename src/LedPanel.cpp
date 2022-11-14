#include "LedPanel.h"

LedPanel::LedPanel()
{
    pinMode(LED_FUN_0_PIN, OUTPUT);
    digitalWrite(LED_FUN_0_PIN, HIGH);
    pinMode(LED_FUN_1_PIN, OUTPUT);
    digitalWrite(LED_FUN_1_PIN, HIGH);
}

void LedPanel::SetLed(uint8_t ledNum, LedBlinkRate rate)
{
    uint8_t pin;
    
    switch (ledNum)
    {
    case 0:
        pin = LED_FUN_0_PIN;
        break;
    case 1:
        pin = LED_FUN_1_PIN;
        break;
    default:
        return;
    }

    switch (rate)
    {
    case LedBlinkRate::RateAlwaysOn:
        ticker.detach();
        digitalWrite(pin, LOW);
        break;
    case LedBlinkRate::Rate8Hz:
        ticker.attach_ms(62, [&pin]() {digitalWrite(pin, !digitalRead(pin));}); // 62.5ms is not allowed
        break;
    case LedBlinkRate::Rate2Hz:
        ticker.attach_ms(250, [&pin]() {digitalWrite(pin, !digitalRead(pin));});
        break;
    case LedBlinkRate::Rate0_5Hz:
        ticker.attach_ms(1000, [&pin]() {digitalWrite(pin, !digitalRead(pin));});
        break;
    case LedBlinkRate::RateAlwaysOff:
        ticker.detach();
        digitalWrite(pin, HIGH);
        break;
    default:
        break;
    }
}
