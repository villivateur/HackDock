#pragma once

#include <Arduino.h>

#define CUSTOM_PIN_0 14
#define CUSTOM_PIN_1 16


class CustomPin
{
public:
    CustomPin();
    void Init();
    void SetStatus(uint32_t pinNum, uint32_t status);
};
