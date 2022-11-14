#include <Arduino.h>
#include <Ticker.h>

#define BEEP_PIN 8


enum class BeepStatus : uint8_t
{
    On,
    Drip,
    Off,
};

class Beep
{
private:
    Ticker ticker;
    void BeepTask();

public:
    Beep();
    void SetStatus(BeepStatus status);
};
