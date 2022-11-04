#include <Arduino.h>
#include "OnlineConnector.h"
#include "UsbConnector.h"
#include "LocalConnector.h"
#include "MonitorItems.h"
#include "StatusLed.h"
#include "WifiConfigManager.h"
#include "UserData.h"
#include "FuncButton.h"

StatusLed* statusLed;
UserData* userdataManager;
WifiConfigManager* wifiConfigManager;
FuncButton* funcButton;

OnlineConnector* onlineConnector;
UsbConnector* usbConnector;
LocalConnector* localConnector;

RunMode runMode;

void RunMode_Usb_Setup()
{
    usbConnector = new UsbConnector();
}

void RunMode_Online_Setup()
{
    if (!userdataManager->WifiInfoValid()) {
        wifiConfigManager = new WifiConfigManager();
        wifiConfigManager->ProcessConfig();
    } else {
        onlineConnector = new OnlineConnector();
    }
}

void RunMode_Local_Setup()
{
    if (!userdataManager->WifiInfoValid()) {
        wifiConfigManager = new WifiConfigManager();
        wifiConfigManager->ProcessConfig();
    } else {
        localConnector = new LocalConnector();
    }
}

void setup()
{
    Serial.begin(115200);

    statusLed = new StatusLed();
    userdataManager = new UserData();
    funcButton = new FuncButton();

    runMode = userdataManager->GetRunMode();

    switch (runMode) {
        case RunMode_Usb:
            RunMode_Usb_Setup();
            break;
        case RunMode_Online:
            RunMode_Online_Setup();
            break;
        case RunMode_Local:
            RunMode_Local_Setup();
            break;
        default:
            runMode = RunMode_Usb;
            userdataManager->SetRunMode(runMode);
            RunMode_Usb_Setup();
            break;
    }
}

void RunMode_Usb_Loop()
{
}

void RunMode_Online_Loop()
{
    if (onlineConnector->FetchNewData() == OK) {
    } else {
    }
}

void RunMode_Local_Loop()
{
    localConnector->FetchNewData();
}

void loop()
{
    delay(1000);
    switch (runMode) {
        case RunMode_Usb:
            RunMode_Usb_Loop();
            break;
        case RunMode_Online:
            RunMode_Online_Loop();
            break;
        case RunMode_Local:
            RunMode_Local_Loop();
            break;
        default:
            break;
    }
}
