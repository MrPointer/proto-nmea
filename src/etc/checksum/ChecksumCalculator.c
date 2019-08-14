//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/etc/checksum/ChecksumCalculator.h"

uint32_t calculateRangeChecksum(const unsigned char *begin, const unsigned char *end)
{
    uint32_t checksum = 0x00;

    if (begin == NULL || !(*begin))
        return 0;

    // ToDo: Optimize
    if (end == NULL || !(*end))
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
