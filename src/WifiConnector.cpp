#include "WifiConnector.h"
#include "EepromUtils.h"

#define MAX_SSID_LEN 32
#define MAX_PASSWD_LEN 32

bool ConfigValid(String data)
{
    if (data.length() >= 3 && data.startsWith("##")) {
        return true;
    }
    return false;
}

STATUS ConnectWifi()
{
    String ssidRaw = EepromUtils::ReadString(EEPROM_WIFI_SSID_OFFSET);
    String passwordRaw = EepromUtils::ReadString(EEPROM_WIFI_PASSWORD_OFFSET);
    String ipStrRaw = EepromUtils::ReadString(EEPROM_WIFI_IP_OFFSET);
    String netmaskStrRaw = EepromUtils::ReadString(EEPROM_WIFI_NETMASK_OFFSET);
    String gatewayStrRaw = EepromUtils::ReadString(EEPROM_WIFI_GATEWAY_OFFSET);

    if (!ConfigValid(ssidRaw) || !ConfigValid(passwordRaw)) {
        return FAIL;
    }

    if (ConfigValid(ipStrRaw) && ConfigValid(netmaskStrRaw) && ConfigValid(gatewayStrRaw)) {
        String ipStr = ipStrRaw.substring(2);
        String netmaskStr = netmaskStrRaw.substring(2);
        String gatewayStr = gatewayStrRaw.substring(2);
        IPAddress ip;
        IPAddress netmask;
        IPAddress gateway;

        ip.fromString(ipStr);
        netmask.fromString(netmaskStr);
        gateway.fromString(gatewayStr);

        if (!WiFi.config(ip, gateway, netmask)) {
            return FAIL;
        }
    }

    String ssid = ssidRaw.substring(2);
    String password = passwordRaw.substring(2);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }

    return OK;
}
