#include <Arduino.h>
#include "SerialInterface.h"
#include "UdpInterface.h"
#include "LedPanel.h"
#include "Beep.h"
#include "FuncButton.h"

LedPanel ledPanel;
Beep beep;
FuncButton funcButton;

SerialInterface serialInterface;
UdpInterface udpInterface;

void setup()
{
    Serial.begin(115200);
    beep.SetStatus(BeepStatus::Drip);
    ledPanel.SetLed(0, LedBlinkRate::Rate8Hz);
    ledPanel.SetLed(1, LedBlinkRate::Rate0_5Hz);


    // WiFi.begin(paramManager.GetWifiSsid(), paramManager.GetWifiPasswd());
    // ledPanel.SetLed(0, LedBlinkRate::Rate8Hz);
    // while (WiFi.status() != WL_CONNECTED)
    // {
    //     delay(1000);
    // }
    // ledPanel.SetLed(0, LedBlinkRate::RateAlwaysOff);

    delay(2000);

}

void loop()
{
    delay(1000);
}
