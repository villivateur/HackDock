#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Ticker.h>

#include "NetProtocal.h"

class UdpInterface
{
private:
    Ticker ticker;
    WiFiUDP Udp;
    uint8_t recvBuf[64];
    uint8_t sendBuf[64];
    void UdpTask();
    void DataHandler(NetPackage* package);
    void OnRead(NetPackage* package);
    void OnWrite(NetPackage* package);

public:
    UdpInterface();
};
