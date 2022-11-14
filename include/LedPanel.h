#include <Arduino.h>
#include <Ticker.h>

#define LED_FUN_0_PIN 7
#define LED_FUN_1_PIN 6


enum class LedBlinkRate : uint8_t
{
    RateAlwaysOn,
    Rate8Hz,
    Rate2Hz,
    Rate0_5Hz,
    RateAlwaysOff,
};

class LedPanel
{
private:
    Ticker ticker;

public:
    LedPanel();
    void SetLed(uint8_t ledNum, LedBlinkRate rate);
};
