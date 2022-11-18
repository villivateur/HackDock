#include <Arduino.h>
#include "WifiConnector.h"
#include "SerialInterface.h"
#include "UdpInterface.h"
#include "LedPanel.h"
#include "Beep.h"
#include "FuncButton.h"
#include "CustomPin.h"
#include "EepromUtils.h"

LedPanel ledPanel;
Beep beep;
CustomPin customPin;
FuncButton funcButton;

SerialInterface serialInterface;
UdpInterface udpInterface;

void setup()
{
    EepromUtils::Init();
    ledPanel.Init();
    beep.Init();
    customPin.Init();
    funcButton.Init();
    serialInterface.Init();

    ledPanel.SetLed(0, LedBlinkRate::Rate2Hz);

    if (ConnectWifi() == OK) {
        udpInterface.Init();
        ledPanel.SetLed(0, LedBlinkRate::RateAlwaysOff);
    } else {
        ledPanel.SetLed(0, LedBlinkRate::Rate8Hz);
    }
}

void loop()
{
}
