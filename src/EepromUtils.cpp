#include "EepromUtils.h"

EepromUtils::EepromUtils()
{
}

void EepromUtils::Init()
{
    EEPROM.begin(EEPROM_SIZE);
}

void EepromUtils::WriteString(uint32_t offset, String data)
{
    for (uint32_t i = 0; i < data.length(); i++) {
        EEPROM.write(offset + i, data[i]);
    }
    EEPROM.write(offset + data.length(), '\0');
}

String EepromUtils::ReadString(uint32_t offset)
{
    char readByte;
    String result;

    for (uint32_t addr = offset;
        ((readByte = EEPROM.read(addr)) != '\0') && (result.length() < EEPROM_MAX_STR_LEN);
        addr++) {
        result += readByte;
    }
    return result;
}

void EepromUtils::Save()
{
    EEPROM.commit();
}

