#pragma once

#include <Arduino.h>

#pragma pack(push, 1)

enum class PROTOCAL_CMD : uint8_t
{
    READ,
    WRITE,
};

struct NetPackage
{
    PROTOCAL_CMD cmd;
    uint32_t index;
    uint8_t buff[59];
}; // 64 bytes total

#pragma pack(pop)
