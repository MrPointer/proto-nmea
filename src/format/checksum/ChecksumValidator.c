//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/checksum/ChecksumValidator.h"

static int8_t validateChecksumFormat(const unsigned char *checksumString)
{
    // Should start with a checksum delimiter
    if (checksumString[0] != PROTOCOL_CHECKSUM_DELIMITER)
    {
        if (strchr(((const char *) checksumString), PROTOCOL_CHECKSUM_DELIMITER))
            return -EMISSING_CHECKSUM_DATA;
        else
            return -EMISSING_CHECKSUM;
    }

    // ToDo: Iterate with for loop
    if (!isHex(checksumString[1]) || !isHex(checksumString[2]))
        return -EINVALID_CHECKSUM;

    return EVALID;
}

static int8_t validateChecksumData(const unsigned char *checksumString, unsigned int calculatedChecksum)
{
    char receivedChecksum[3] = {0};

    memcpy(receivedChecksum, checksumString + 1, 2);

    int receivedChecksumValue = stringToHex((const unsigned char *) receivedChecksum);

    if (calculatedChecksum != receivedChecksumValue)
        return -EWRONG_CHECKSUM;

    return EVALID;
}

#ifdef UNIT_TEST

int8_t validateChecksum_testWrapper(const unsigned char *buffer, unsigned int calculatedChecksum)
{
    return validateChecksum(buffer, calculatedChecksum);
}

#endif

#ifdef UNIT_TEST

static
#endif
int8_t validateChecksum(const unsigned char *buffer, unsigned int calculatedChecksum)
{
    uint8_t errorCode = validateChecksumFormat(buffer);
    if (errorCode)
        return errorCode;

    errorCode = validateChecksumData(buffer, calculatedChecksum);
    if (errorCode)
        return errorCode;

    return EVALID;
}
