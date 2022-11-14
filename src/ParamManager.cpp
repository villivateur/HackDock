#include "ParamManager.h"
#include <EEPROM.h>

#define MAX_USER_DATA_SIZE 0x200

#define USER_DATA_VALID_MAGIC 0xaa

#define WIFI_INFO_VALID_OFFSET 0x00
#define WIFI_SSID_VALID 0x20
#define WIFI_PASSWORD_OFFSET 0x40

#define RUN_MODE_OFFSET 0x60

ParamManager::ParamManager()
{
    EEPROM.begin(MAX_USER_DATA_SIZE);
}

String ParamManager::ReadEepromString(uint32_t offset)
{
    String result;
    char readByte;

    for (uint32_t addr = offset; (readByte = EEPROM.read(addr)) != '\0'; addr++) {
        result += readByte;
    }
    return result;
}

void ParamManager::WriteEepromString(String data, uint32_t offset)
{
    for (uint32_t i = 0; i < data.length(); i++) {
        EEPROM.write(i + offset, data[i]);
    }
    EEPROM.write(data.length() + offset, 0x00);
}

void ParamManager::EraseAllData()
{
    EEPROM.write(WIFI_INFO_VALID_OFFSET, 0x00);
    EEPROM.commit();
}

bool ParamManager::WifiInfoValid()
{
    byte validation = EEPROM.read(WIFI_INFO_VALID_OFFSET);
    return validation == USER_DATA_VALID_MAGIC;
}

void ParamManager::ConfirmWifiData()
{
    EEPROM.write(WIFI_INFO_VALID_OFFSET, USER_DATA_VALID_MAGIC);
    EEPROM.commit();
}

String ParamManager::GetWifiSsid()
{
    return ReadEepromString(WIFI_SSID_VALID);
}

void ParamManager::SetWifiSsid(String ssid)
{
    return WriteEepromString(ssid, WIFI_SSID_VALID);
}

String ParamManager::GetWifiPasswd()
{
    return ReadEepromString(WIFI_PASSWORD_OFFSET);
}

void ParamManager::SetWifiPasswd(String password)
{
    return WriteEepromString(password, WIFI_PASSWORD_OFFSET);
}
