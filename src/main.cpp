#include <Arduino.h>
#include "WifiConnector.h"
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
    ledPanel.Init();
    beep.Init();
    funcButton.Init();

    if (ConnectWifi() == OK) {
        udpInterface.Init();
    }

    serialInterface.Init();

    delay(2000);
}

void loop()
{
    delay(1000);
}
