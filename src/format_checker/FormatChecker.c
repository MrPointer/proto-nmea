//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/FormatChecker.h"

int8_t validateMessageFormat(const char *rawMessage)
{
    if (rawMessage[0] != PROTOCOL_START_CHAR)
        return -EINVAL_PROTO_START;
    return 0;
}
