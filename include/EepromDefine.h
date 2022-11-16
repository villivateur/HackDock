#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 0x200

#define WIFI_INFO_VALID_MAGIC 0xaa

#define WIFI_INFO_VALID_OFFSET 0x00
#define WIFI_SSID_OFFSET 0x20
#define WIFI_PASSWORD_OFFSET 0x40