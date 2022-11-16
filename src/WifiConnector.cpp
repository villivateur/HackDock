#include "WifiConnector.h"
#include <EepromDefine.h>

#define MAX_SSID_LEN 32
#define MAX_PASSWD_LEN 32


STATUS ConnectWifi()
{
    // EEPROM.begin(EEPROM_SIZE);
    // byte validation = EEPROM.read(WIFI_INFO_VALID_OFFSET);
    // if (validation != WIFI_INFO_VALID_MAGIC) {
    //     return FAIL;
    // }

    // String ssid;
    // String password;
    // char readByte;

    // for (uint32_t addr = WIFI_SSID_OFFSET;
    //     ((readByte = EEPROM.read(addr)) != '\0') && (ssid.length() < MAX_SSID_LEN);
    //     addr++) {
    //     ssid += readByte;
    // }

    // if (ssid.length() >= MAX_SSID_LEN) {
    //     return FAIL;
    // }

    // for (uint32_t addr = WIFI_PASSWORD_OFFSET;
    //     ((readByte = EEPROM.read(addr)) != '\0') && (password.length() < MAX_PASSWD_LEN);
    //     addr++) {
    //     password += readByte;
    // }

    // if (password.length() >= MAX_SSID_LEN) {
    //     return FAIL;
    // }

    // WiFi.begin(ssid, password);
    WiFi.begin("test", "testtest");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }

    return OK;
}
