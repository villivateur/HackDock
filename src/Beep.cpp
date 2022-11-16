#include "Beep.h"

Beep::Beep()
{
    pinMode(BEEP_PIN, OUTPUT);
    digitalWrite(BEEP_PIN, LOW);
}

void Beep::Init()
{
}

void Beep::BeepTask()
{
    digitalWrite(BEEP_PIN, !digitalRead(BEEP_PIN));     // set pin to the opposite state
}

void Beep::SetStatus(BeepStatus status)
{
    switch (status)
    {
    case BeepStatus::On:
        ticker.detach();
        digitalWrite(BEEP_PIN, HIGH);
        break;
    case BeepStatus::Drip:
        ticker.attach_ms(500, std::bind(&Beep::BeepTask, this));
        break;
    case BeepStatus::Off:
        ticker.detach();
        digitalWrite(BEEP_PIN, LOW);
        break;
    default:
        break;
    }
}
