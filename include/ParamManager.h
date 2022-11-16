#pragma once

#include <Arduino.h>


class ParamManager
{
private:
    String ReadEepromString(uint32_t offset);
    void WriteEepromString(String data, uint32_t offset);

public:
    ParamManager();
    void EraseAllData();

    bool WifiInfoValid();
    void ConfirmWifiData();
    String GetWifiSsid();
    void SetWifiSsid(String ssid);
    String GetWifiPasswd();
    void SetWifiPasswd(String password);
};
