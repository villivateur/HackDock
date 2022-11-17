#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 0x200
#define EEPROM_MAX_STR_LEN 0x20

#define EEPROM_RESERVED_ADDR 0x00
#define EEPROM_WIFI_SSID_OFFSET 0x20
#define EEPROM_WIFI_PASSWORD_OFFSET 0x40
#define EEPROM_WIFI_IP_OFFSET 0x60
#define EEPROM_WIFI_NETMASK_OFFSET 0x80
#define EEPROM_WIFI_GATEWAY_OFFSET 0xa0

class EepromUtils
{
public:
    EepromUtils();
    static void Init();
    static void WriteString(uint32_t offset, String data);
    static String ReadString(uint32_t offset);
    static void Save();
};
