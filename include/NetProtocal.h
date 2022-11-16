#pragma once

#include <Arduino.h>

#pragma pack(push, 1)

enum class REQUEST_CMD : uint8_t
{
    READ_CMD = 0,
    READ_RESP = 1,

    WRITE_CMD = 2,
    WRITE_RESP = 3,
};

enum class RESPOND_CODE : uint8_t
{
    OK = 0,
    BAD_REQUEST = 1,
    FORBIDDEN = 2,
    INTERNAL_ERROR = 3,
    OTHER_ERROR,
};

struct RequestPackage
{
    uint32_t packageId;
    REQUEST_CMD cmd;
    uint16_t index;
    uint32_t value;
};

struct ResponsePackage
{
    uint32_t packageId;
    RESPOND_CODE code;
    uint32_t value;
};

#pragma pack(pop)
