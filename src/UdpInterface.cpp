#include "UdpInterface.h"
#include "ParamManager.h"

UdpInterface::UdpInterface()
{
    Udp.begin(6666);

    ticker.attach_ms(50, std::bind(&UdpInterface::UdpTask, this));
}

void UdpInterface::UdpTask()
{
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        int len = Udp.read(recvBuf, sizeof(NetPackage));
        
        DataHandler((NetPackage*)recvBuf);

        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(sendBuf, 2);
        Udp.endPacket();
    }
}

void UdpInterface::DataHandler(NetPackage* package)
{
    switch (package->cmd)
    {
    case PROTOCAL_CMD::READ:
        OnRead(package);
        break;
    case PROTOCAL_CMD::WRITE:
        OnWrite(package);
        break;
    default:
        break;
    }
}

void UdpInterface::OnRead(NetPackage* package)
{

}

void UdpInterface::OnWrite(NetPackage* package)
{

}
