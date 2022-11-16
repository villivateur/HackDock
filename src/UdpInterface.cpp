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
    Udp.begin(6666);

    ticker.attach_ms(50, std::bind(&UdpInterface::UdpTask, this));
}

void UdpInterface::UdpTask()
{
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        int len = Udp.read(recvBuf, sizeof(RequestPackage));
        if (len != sizeof(RequestPackage)) {
            SendResponse(0, RESPOND_CODE::BAD_REQUEST, 0);
            return;
        }
        DataHandler((RequestPackage*)recvBuf);
    }
}

void UdpInterface::DataHandler(RequestPackage* package)
{
    uint32_t actionMap = COMBINE(package->cmd, package->index);

    switch (actionMap)
    {
    case COMBINE(REQUEST_CMD::WRITE_CMD, 0x1000): // LED0
        ledPanel.SetLed(0, (LedBlinkRate)package->value);
        SendResponse(package->packageId, RESPOND_CODE::OK, 0);
        break;
    case COMBINE(REQUEST_CMD::WRITE_CMD, 0x1001): // LED1
        ledPanel.SetLed(1, (LedBlinkRate)package->value);
        SendResponse(package->packageId, RESPOND_CODE::OK, 0);
        break;
    case COMBINE(REQUEST_CMD::WRITE_CMD, 0x1010): // Beep
        beep.SetStatus((BeepStatus)package->value);
        SendResponse(package->packageId, RESPOND_CODE::OK, 0);
        break;
    case COMBINE(REQUEST_CMD::READ_CMD, 0x2000): // Button
        SendResponse(package->packageId, RESPOND_CODE::OK, funcButton.MsSinceLastPress());
        break;
    default:
        SendResponse(package->packageId, RESPOND_CODE::FORBIDDEN, 0);
        break;
    }
}

void UdpInterface::SendResponse(uint32_t packageId, RESPOND_CODE code, uint32_t value)
{
    ResponsePackage package {
        .packageId = packageId,
        .code = code,
        .value = value,
    };

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write((uint8_t*)&package, sizeof(ResponsePackage));
    Udp.endPacket();
}
