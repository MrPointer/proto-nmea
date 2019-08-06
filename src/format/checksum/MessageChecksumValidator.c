//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/checksum/MessageChecksumValidator.h"

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

static int8_t validateChecksumString(const unsigned char *buffer, unsigned int calculatedChecksum)
{
    uint8_t errorCode = validateChecksumFormat(buffer);
    if (errorCode)
        return errorCode;

    errorCode = validateChecksumData(buffer, calculatedChecksum);
    if (errorCode)
        return errorCode;

    return EVALID;
}

#ifdef UNIT_TEST

static
#endif
int8_t validateMessageChecksum(const unsigned char *message, size_t messageSize)
{
    // Find checksum delimiter index
    size_t checksumDelimiterPosition = messageSize - PROTOCOL_STOP_LENGTH - CHECKSUM_FULL_LENGTH;

    // Calculate message's checksum
    int calculatedChecksum = calculateChecksum(message + MESSAGE_TYPE_START_INDEX,
                                               message + checksumDelimiterPosition);

    return validateChecksumString(message + checksumDelimiterPosition, calculatedChecksum);
}

#ifdef UNIT_TEST

int8_t validateMessageChecksum_testWrapper(const unsigned char *message, size_t messageSize)
{
    return validateMessageChecksum(message, messageSize);
}

#endif

