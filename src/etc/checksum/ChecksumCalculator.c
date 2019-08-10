//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/etc/checksum/ChecksumCalculator.h"

uint32_t calculateChecksum(const unsigned char *begin, const unsigned char *end)
{
    uint32_t checksum = 0x00;

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
