//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/ChecksumValidator.h"

static int8_t validateChecksumFormat(const unsigned char *message, size_t checksumIdealIndex)
{
    // Should start with a checksum delimiter
    if (message[checksumIdealIndex] != PROTOCOL_CHECKSUM_DELIMITER)
    {
        if (strchr(((const char *) message + checksumIdealIndex), PROTOCOL_CHECKSUM_DELIMITER))
            return -EMISSING_CHECKSUM_DATA;
        else
            return -EMISSING_CHECKSUM;
    }

    if (!isHex(message[checksumIdealIndex + 1]) || !isHex(message[checksumIdealIndex + 2]))
        return -EINVALID_CHECKSUM;

    return EVALID;
}

static int8_t validateChecksumData(const unsigned char *message, size_t checksumDelimiterIndex)
{
    char receivedChecksum[3] = {0};

    memcpy(receivedChecksum, message + checksumDelimiterIndex + 1, 2);

    int calculatedChecksum = calculateChecksum(message + MESSAGE_TYPE_START_INDEX, message + checksumDelimiterIndex);
    int receivedChecksumValue = stringToHex((const unsigned char *) receivedChecksum);

    if (calculatedChecksum != receivedChecksumValue)
        return -EWRONG_CHECKSUM;

    return EVALID;
}

#ifdef UNIT_TEST

int8_t validateChecksum_testWrapper(const unsigned char *message, size_t messageSize)
{
    return validateChecksum(message, messageSize);
}

#endif

#ifdef UNIT_TEST

static
#endif
int8_t validateChecksum(const unsigned char *message, size_t messageSize)
{
    if (IS_NULL_STRING(message))
        return -ENULL_STRING;

    // Calculate checksum index
    size_t checksumDelimiterPosition = messageSize - PROTOCOL_STOP_LENGTH - CHECKSUM_FULL_LENGTH;

    uint8_t errorCode = validateChecksumFormat(message, checksumDelimiterPosition);
    if (errorCode)
        return errorCode;

    errorCode = validateChecksumData(message, checksumDelimiterPosition);
    if (errorCode)
        return errorCode;

    return EVALID;
}
