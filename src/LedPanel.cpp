#include "LedPanel.h"

LedPanel::LedPanel()
{
    leds[0].pin = LED_FUN_0_PIN;
    leds[1].pin = LED_FUN_1_PIN;

    for (int i = 0; i < LED_NUM; i++) {
        pinMode(leds[i].pin, OUTPUT);
        digitalWrite(leds[i].pin, HIGH);
    }
}

void LedPanel::Init()
{
}

void LedPanel::SetLed(uint8_t ledNum, LedBlinkRate rate)
{
    LedItem* led;
    
    switch (ledNum)
    {
    case 0:
        led = &(leds[0]);
        break;
    case 1:
        led = &(leds[1]);
        break;
    default:
        return;
    }

    switch (rate)
    {
    case LedBlinkRate::RateAlwaysOn:
        led->ticker.detach();
        digitalWrite(led->pin, LOW);
        break;
    case LedBlinkRate::Rate8Hz:
        led->ticker.attach_ms(62, [led]() {digitalWrite(led->pin, !digitalRead(led->pin));}); // 62.5ms is not allowed
        break;
    case LedBlinkRate::Rate2Hz:
        led->ticker.attach_ms(250, [led]() {digitalWrite(led->pin, !digitalRead(led->pin));});
        break;
    case LedBlinkRate::Rate0_5Hz:
        led->ticker.attach_ms(1000, [led]() {digitalWrite(led->pin, !digitalRead(led->pin));});
        break;
    case LedBlinkRate::RateAlwaysOff:
        led->ticker.detach();
        digitalWrite(led->pin, HIGH);
        break;
    default:
        break;
    }
}
