//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/FormatChecker.h"

int8_t validateMessageFormat(const char *rawMessage)
{
    size_t messageLength;
    char receivedChecksum[3] = {0};

    if (rawMessage == NULL || *rawMessage == '\0')
        return -ENULL_STRING;

    // Validate message beginning fits protocol
    if (*rawMessage != PROTOCOL_START_CHAR)
        return -EINVALID_PROTOCOL_BEGINNING;

    messageLength = strlen(rawMessage); // Figure out the length of the message

    // Validate message ending fits protocol
    if (rawMessage[messageLength - 2] != PROTOCOL_STOP_CHAR_1 ||
        rawMessage[messageLength - 1] != PROTOCOL_STOP_CHAR_2)
        return -EINVALID_PROTOCOL_ENDING;

    if (messageLength <= MESSAGE_MIN_LENGTH)
    {
        if (messageLength < MESSAGE_MIN_LENGTH)
            return -ESHORT_MESSAGE;
        else
            return -EMISSING_MESSAGE_DATA;
    }
    else if (messageLength > MESSAGE_MAX_LENGTH)
        return -ELONG_MESSAGE;

    // Validate checksum
    size_t checkSumIdealIndex = messageLength - PROTOCOL_STOP_LENGTH - CHECKSUM_FULL_LENGTH;
    // Should start with a checksum delimiter
    if (rawMessage[checkSumIdealIndex] != PROTOCOL_CHECKSUM_DELIMITER)
    {
        if (strchr(rawMessage + checkSumIdealIndex, PROTOCOL_CHECKSUM_DELIMITER))
            return -EMISSING_CHECKSUM_DATA;
        else
            return -EMISSING_CHECKSUM;
    }
    /*// Should be followed by 2 integers representing the checksum
    if (!isdigit(rawMessage[checkSumIdealIndex + 1]) || !isdigit(rawMessage[checkSumIdealIndex + 2]))
        return -EINVALID_CHECKSUM;*/

    for (int i = MESSAGE_TYPE_START_INDEX; i <= MESSAGE_TYPE_START_INDEX + MESSAGE_TYPE_MIN_LENGTH; ++i)
    {
        if (!isalpha(rawMessage[i])) // Each char representing message type must be an alpha
            return -EINVALID_MESSAGE_TYPE;
    }

    // ToDo: Optimize
    memcpy(receivedChecksum, rawMessage + checkSumIdealIndex + 1, 2);

    int calculatedChecksum = calculateChecksum(rawMessage + MESSAGE_TYPE_START_INDEX, rawMessage + checkSumIdealIndex);

    int receivedChecksumValue = stringToHex((const unsigned char *) receivedChecksum);

    if (calculatedChecksum != receivedChecksumValue)
        return -EWRONG_CHECKSUM;

    return 0;
}
