#include "SerialInterface.h"

SerialInterface::SerialInterface()
{
    Serial.begin(115200);
    halfReceived = false;
}

void SerialInterface::Init()
{
    ticker.attach_ms(50, std::bind(&SerialInterface::SerialTask, this));
}

void SerialInterface::SerialTask()
{
    while (Serial.available()) {
        buffer.push(Serial.read());
    }

    while (buffer.size() > 6) {
        SerialRequest* package = (SerialRequest*)currentBuf;
        uint8_t* lengthPtr = (uint8_t*)&package->length;

        buffer.pop((uint8_t&)package->cmd);
        buffer.pop(package->subCmd);
        buffer.pop(*lengthPtr);
        buffer.pop(*(lengthPtr + 1));
        buffer.pop(*(lengthPtr + 2));
        buffer.pop(*(lengthPtr + 3));

        if (buffer.size() < package->length - 6) {
            halfReceived = true;
            return;
        }

        
    }
}
