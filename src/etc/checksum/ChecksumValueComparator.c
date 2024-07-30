//
// Created by Timor Gruber on 08/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/etc/checksum/ChecksumValueComparator.h"

#ifdef UNIT_TEST

static
#endif
int compareChecksumData(const unsigned char *checksumString, unsigned int calculatedChecksum)
{
    if (IS_NULL_STRING(checksumString))
        return -1;

    unsigned int receivedChecksumValue = substringToHex(checksumString, 0, 2);

    return (int) receivedChecksumValue - (int) calculatedChecksum;
}

#ifdef UNIT_TEST

int compareChecksumData_testWrapper(const unsigned char *checksumString, unsigned int calculatedChecksum)
{
    return compareChecksumData(checksumString, calculatedChecksum);
}

#endif
