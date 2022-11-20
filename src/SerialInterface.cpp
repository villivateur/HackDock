#include "SerialInterface.h"
#include "EepromUtils.h"

#define MAX_CMD_LEN 100

SerialInterface::SerialInterface()
{
    Serial.begin(115200);
    cmdLine = "";
    halfReceived = false;
}

void SerialInterface::Init()
{
    ticker.attach_ms(50, std::bind(&SerialInterface::SerialTask, this));
}

void SerialInterface::SerialTask()
{
    while (Serial.available()) {
        ringBuffer.push(Serial.read());
    }

    while (ringBuffer.size() > 0) {
        if (cmdLine.endsWith(";")) {
            cmdLine.clear();
        }
        
        uint8_t readByte;
        ringBuffer.pop(readByte);
        if (cmdLine.isEmpty() && isspace(readByte)) {
            continue;
        }
        cmdLine += (char)readByte;

        if (cmdLine.length() > MAX_CMD_LEN) {
            Serial.println("Command too long, max 100 bytes");
            Serial.println(cmdLine);
            cmdLine.clear();
            continue;
        }
        if (cmdLine.endsWith(";")) {
            if (cmdLine.startsWith("AT")) {
                CmdHandler(cmdLine);
            } else {
                Serial.println("Command should start with AT");
                continue;
            }
        }
    }
}

void SerialInterface::CmdHandler(String cmdLine)
{
    if (cmdLine == "AT;") {
        Serial.println("OK");
    } else if (cmdLine.length() <= 4) {
        Serial.println("Bad Command");
    } else if (cmdLine[strlen("AT")] != '+') {
        Serial.println("Bad Command");
    } else {
        String realCmd = cmdLine.substring(3, cmdLine.length() - 1);
        ParseCmd(realCmd);
    }
}

void SerialInterface::ParseCmd(String cmd)
{
    if (cmd == "STARTCONFIG") {
        Serial.println("Not implement");

    } else if (cmd == "SAVECONFIG") {
        EepromUtils::Save();
        Serial.println("Saved");

    } else if (cmd.startsWith("SETSN") && cmd[strlen("SETSN")] == '=') {
        Serial.println("Not implement");

    } else if (cmd.startsWith("SETSSID") && cmd[strlen("SETSSID")] == '=') {
        EepromUtils::WriteString(EEPROM_WIFI_SSID_OFFSET, "##"+cmd.substring(strlen("SETSSID") + 1));
        Serial.println("SSID: " + cmd.substring(strlen("SETSSID") + 1));

    } else if (cmd.startsWith("SETPASS") && cmd[strlen("SETPASS")] == '=') {
        EepromUtils::WriteString(EEPROM_WIFI_PASSWORD_OFFSET, "##"+cmd.substring(strlen("SETPASS") + 1));
        Serial.println("Password: " + cmd.substring(strlen("SETPASS") + 1));

    } else if (cmd.startsWith("SETIP") && cmd[strlen("SETIP")] == '=') {
        EepromUtils::WriteString(EEPROM_WIFI_IP_OFFSET, "##"+cmd.substring(strlen("SETIP") + 1));
        Serial.println("IP: " + cmd.substring(strlen("SETIP") + 1));

    } else if (cmd.startsWith("SETNETMASK") && cmd[strlen("SETNETMASK")] == '=') {
        EepromUtils::WriteString(EEPROM_WIFI_NETMASK_OFFSET, "##"+cmd.substring(strlen("SETNETMASK") + 1));
        Serial.println("Net mask: " + cmd.substring(strlen("SETNETMASK") + 1));

    } else if (cmd.startsWith("SETGATEWAY") && cmd[strlen("SETGATEWAY")] == '=') {
        EepromUtils::WriteString(EEPROM_WIFI_GATEWAY_OFFSET, "##"+cmd.substring(strlen("SETGATEWAY") + 1));
        Serial.println("Gateway: " + cmd.substring(strlen("SETGATEWAY") + 1));

    } else if (cmd.startsWith("CLEARCONFIG")) {
        EepromUtils::WriteString(EEPROM_WIFI_SSID_OFFSET, "xxx");
        EepromUtils::WriteString(EEPROM_WIFI_PASSWORD_OFFSET, "xxx");
        EepromUtils::WriteString(EEPROM_WIFI_IP_OFFSET, "xxx");
        EepromUtils::WriteString(EEPROM_WIFI_NETMASK_OFFSET, "xxx");
        EepromUtils::WriteString(EEPROM_WIFI_GATEWAY_OFFSET, "xxx");
        EepromUtils::Save();
        Serial.println("Config cleared");

    } else {
        Serial.println("Bad Command");
    }
}
