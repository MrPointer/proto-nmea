//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/FormatChecker.h"

int8_t validateMessageFormat(const char *rawMessage)
{
    size_t messageLength;

    if (*rawMessage != PROTOCOL_START_CHAR)
        return -EINVALID_PROTOCOL_START;

    messageLength = strlen(rawMessage); // Figure out the length of the message

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
