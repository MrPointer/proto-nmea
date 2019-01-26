//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/FormatChecker.h"

int8_t validateMessageFormat(const char *rawMessage)
{
    size_t messageLength;

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

    for (int i = 1; i < messageLength; ++i)
    {
        if (i == PROTOCOL_DATA_START_INDEX)
        {
            if (rawMessage[i] == PROTOCOL_FIELD_DELIMITER)
                return -EMISPLACED_DELIMITER;
        }
        else if (i > PROTOCOL_DATA_START_INDEX && i < MESSAGE_DATA_START_INDEX)
        {
            if (rawMessage[i] == PROTOCOL_FIELD_DELIMITER)
                return -EMISPLACED_DELIMITER;
        }
    }

    return 0;
}
