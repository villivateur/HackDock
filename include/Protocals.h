#pragma once

#include <Arduino.h>

#pragma pack(push, 1)

enum class REQUEST_CMD : uint8_t
{
    READ = 0,
    WRITE = 1,
};

enum class RESPOND_CODE : uint8_t
{
    OK = 0,
    BAD_REQUEST = 1,
    FORBIDDEN = 2,
    INTERNAL_ERROR = 3,
    OTHER_ERROR,
};

struct UdpRequest
{
    uint32_t packageId;
    REQUEST_CMD cmd;
    uint16_t index;
    uint32_t value;
};

struct UdpResponse
{
    uint32_t packageId;
    RESPOND_CODE code;
    uint32_t value;
};

struct SerialRequest
{
    REQUEST_CMD cmd;
    uint8_t subCmd;
    uint32_t length; // include cmd and subCmd;
    uint8_t buf[1]; // Dynamic size
};

#pragma pack(pop)
