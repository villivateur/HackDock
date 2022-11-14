#include <Arduino.h>
#include "UsbDataHandler.h"
#include "UdpDataHandler.h"
#include "LedPanel.h"
#include "ParamManager.h"
#include "FuncButton.h"

LedPanel ledPanel;
ParamManager paramManager;
FuncButton funcButton;

UsbDataHandler usbDataHandler;
UdpDataHandler udpDataHandler;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(paramManager.GetWifiSsid(), paramManager.GetWifiPasswd());
    ledPanel.SetLed(0, LedBlinkRate::Rate8Hz);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }
    ledPanel.SetLed(0, LedBlinkRate::RateAlwaysOff);

    delay(2000);

}

void loop()
{
    delay(1000);
}
