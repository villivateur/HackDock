#include "CustomPin.h"

CustomPin::CustomPin()
{
    pinMode(CUSTOM_PIN_0, OUTPUT);
    pinMode(CUSTOM_PIN_1, OUTPUT);
    digitalWrite(CUSTOM_PIN_0, LOW);
    digitalWrite(CUSTOM_PIN_1, LOW);
}

void CustomPin::Init()
{
}

void CustomPin::SetStatus(uint32_t pinNum, uint32_t status)
{
    uint32_t gpio = 0;

    switch (pinNum)
    {
    case 0:
        gpio = CUSTOM_PIN_0;
        break;
    case 1:
        gpio = CUSTOM_PIN_1;
        break;
    default:
        return;
    }

    switch (status)
    {
    case 0:
        digitalWrite(gpio, LOW);
        break;
    case 1:
        digitalWrite(gpio, HIGH);
        break;
    default:
        return;
    }
}
