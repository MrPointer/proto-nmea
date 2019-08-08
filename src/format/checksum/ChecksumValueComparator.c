//
// Created by Timor Gruber on 08/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/checksum/ChecksumValueComparator.h"

#ifdef UNIT_TEST

static
#endif
int compareChecksumData(const unsigned char *checksumString, unsigned int calculatedChecksum)
{
    char receivedChecksum[3] = {0};

    memcpy(receivedChecksum, checksumString + 1, 2);

    unsigned int receivedChecksumValue = stringToHex((const unsigned char *) receivedChecksum);

    return (int) receivedChecksumValue - (int) calculatedChecksum;
}

#ifdef UNIT_TEST

int compareChecksumData_testWrapper(const unsigned char *checksumString, unsigned int calculatedChecksum)
{
    return compareChecksumData(checksumString, calculatedChecksum);
}

#endif
