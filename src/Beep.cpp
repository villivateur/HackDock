#include "Beep.h"

static void BeepTask()
{
    digitalWrite(BEEP_PIN, !digitalRead(BEEP_PIN));     // set pin to the opposite state
}

void Beep::SetStatus(BeepStatus status)
{
    switch (status)
    {
    case BeepStatus::On:
        beepTicker.detach();
        digitalWrite(BEEP_PIN, HIGH);
        break;
    case BeepStatus::Drip:
        beepTicker.attach(0.5, BeepTask);
        break;
    case BeepStatus::Off:
        beepTicker.detach();
        digitalWrite(BEEP_PIN, LOW);
        break;
    default:
        break;
    }
}

Beep::Beep()
{
    pinMode(BEEP_PIN, OUTPUT);
    digitalWrite(BEEP_PIN, LOW);
}
