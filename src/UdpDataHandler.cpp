#include "UdpDataHandler.h"
#include "LedPanel.h"
#include "ParamManager.h"

static uint8_t packRecv[256];

UdpDataHandler::UdpDataHandler()
{
    data = (UdpData*)(packRecv + 4);
    uint32_t port = 32737;
    Udp.begin(port);

    ticker.attach_ms(50, std::bind(&UdpDataHandler::UdpTask, this));
}

void UdpDataHandler::UdpTask()
{
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        int len = Udp.read(packRecv, 255);
        uint8_t packSend[2];

        if (len <= 0) {
            return;
        }
        if (packRecv[0] == 0x19 && packRecv[1] == 0x26 && packRecv[2] == 0x08 && packRecv[3] == 0x17) {
            packSend[0] = 0x00;
            packSend[1] = 0x00;
        } else {
            packSend[0] = 0x11;
            packSend[1] = 0x22;
            memset(packRecv, 0, sizeof(packRecv));
        }

        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(packSend, 2);
        Udp.endPacket();
    }
}
