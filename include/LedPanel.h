#pragma once

#include <Arduino.h>
#include <Ticker.h>

#define LED_NUM 2

#define LED_FUN_0_PIN 13
#define LED_FUN_1_PIN 12


enum class LedBlinkRate : uint8_t
{
    RateAlwaysOn,
    Rate8Hz,
    Rate2Hz,
    Rate0_5Hz,
    RateAlwaysOff,
};

struct LedItem
{
    Ticker ticker;
    uint8_t pin;
};

class LedPanel
{
private:
    LedItem leds[LED_NUM];

public:
    LedPanel();
    void SetLed(uint8_t ledNum, LedBlinkRate rate);
};
