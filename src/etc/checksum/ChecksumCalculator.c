//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/etc/checksum/ChecksumCalculator.h"

#ifdef UNIT_TEST

static
#endif
uint32_t calculateRangeChecksum(const unsigned char *begin, const unsigned char *end)
{
    uint32_t checksum = 0x00;

    if (IS_NULL_STRING(begin))
        return 0;

    if (IS_NULL_STRING(end))
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

#ifdef UNIT_TEST

uint32_t calculateRangeChecksum_testWrapper(const unsigned char *begin, const unsigned char *end)
{ return calculateRangeChecksum(begin, end); }

#endif

#ifdef UNIT_TEST

static uint32_t calculateLengthChecksum(const unsigned char *str, size_t length)
{ return calculateRangeChecksum(str, str + length); }

uint32_t calculateLengthChecksum_testWrapper(const unsigned char *str, size_t length)
{ return calculateLengthChecksum(str, length); }

static uint32_t calculateChecksum(const unsigned char *str)
{ return calculateRangeChecksum(str, NULL); }

uint32_t calculateChecksum_testWrapper(const unsigned char *str)
{ return calculateChecksum(str); }

#endif
