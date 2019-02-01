//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/utility/ChecksumUtils.h"

int calculateChecksum(const char *begin, const char *end)
{
    int checksum = 0x00;

    if (begin == NULL)
        return -ENULL_STRING;

    // ToDo: Optimize
    if (end == NULL)
    {
        while (*begin)
            checksum ^= *begin++;
    }
    else
    {
        while (*begin && *begin != *end)
            checksum ^= *begin++;
    }

    return checksum;
}
