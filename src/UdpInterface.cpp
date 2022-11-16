#include "UdpInterface.h"
#include "LedPanel.h"
#include "Beep.h"
#include "FuncButton.h"

extern LedPanel ledPanel;
extern Beep beep;
extern FuncButton funcButton;

#define COMBINE(x, y) (((uint32_t)(x)) << 16) | ((uint32_t)(y))

UdpInterface::UdpInterface()
{
}

void UdpInterface::Init()
{
    Udp.begin(6666);
    ticker.attach_ms(50, std::bind(&UdpInterface::UdpTask, this));
}

void UdpInterface::UdpTask()
{
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        int len = Udp.read(recvBuf, sizeof(UdpRequest));
        if (len != sizeof(UdpRequest)) {
            SendResponse(0, RESPOND_CODE::BAD_REQUEST, 0);
            return;
        }
        DataHandler((UdpRequest*)recvBuf);
    }
}

void UdpInterface::DataHandler(UdpRequest* package)
{
    uint32_t actionMap = COMBINE(package->cmd, package->index);

    switch (actionMap)
    {
    case COMBINE(REQUEST_CMD::READ, 0x0000): // Ping
        SendResponse(package->packageId, RESPOND_CODE::OK, 0x19260817);
        break;
    case COMBINE(REQUEST_CMD::READ, 0x0001): // Product ID
        SendResponse(package->packageId, RESPOND_CODE::OK, 27);
        break;
    case COMBINE(REQUEST_CMD::READ, 0x0002): // Serial Num
        SendResponse(package->packageId, RESPOND_CODE::OK, 0);
        break;
    case COMBINE(REQUEST_CMD::WRITE, 0x1000): // LED0
        ledPanel.SetLed(0, (LedBlinkRate)package->value);
        SendResponse(package->packageId, RESPOND_CODE::OK, 0);
        break;
    case COMBINE(REQUEST_CMD::WRITE, 0x1001): // LED1
        ledPanel.SetLed(1, (LedBlinkRate)package->value);
        SendResponse(package->packageId, RESPOND_CODE::OK, 0);
        break;
    case COMBINE(REQUEST_CMD::WRITE, 0x1010): // Beep
        beep.SetStatus((BeepStatus)package->value);
        SendResponse(package->packageId, RESPOND_CODE::OK, 0);
        break;
    case COMBINE(REQUEST_CMD::READ, 0x2000): // Button
        SendResponse(package->packageId, RESPOND_CODE::OK, funcButton.MsSinceLastPress());
        break;
    default:
        SendResponse(package->packageId, RESPOND_CODE::FORBIDDEN, 0);
        break;
    }
}

void UdpInterface::SendResponse(uint32_t packageId, RESPOND_CODE code, uint32_t value)
{
    UdpResponse package {
        .packageId = packageId,
        .code = code,
        .value = value,
    };

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write((uint8_t*)&package, sizeof(UdpResponse));
    Udp.endPacket();
}
