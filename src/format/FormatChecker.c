//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/FormatChecker.h"

//region Helper Macros Definitions

#define VALIDATE_MESSAGE_BEGINNING_FITS_PROTOCOL(message) \
    if (*(message) != PROTOCOL_START_CHAR) \
        return -EINVALID_PROTOCOL_BEGINNING;

#define VALIDATE_MESSAGE_ENDING_FITS_PROTOCOL(message, messageSize) \
    if ((message)[(messageSize) - 2] != PROTOCOL_STOP_CHAR_1 || \
        (message)[(messageSize) - 1] != PROTOCOL_STOP_CHAR_2) \
            return -EINVALID_PROTOCOL_ENDING;

//endregion

//region Helper Functions Declaration

static int8_t validateMessageLengthInRange(size_t messageSize);

static int8_t validateMessageType(const char *message);

//endregion

//region API

int8_t validateMessageFormat(const char *message)
{
    size_t messageSize = strlen(message);

    return validateFixedSizeMessageFormat(message, messageSize);
}

int8_t validateFixedSizeMessageFormat(const char *rawMessage, size_t messageSize)
{
    if (IS_NULL_STRING(rawMessage))
        return -ENULL_STRING;

    VALIDATE_MESSAGE_BEGINNING_FITS_PROTOCOL(rawMessage)
    VALIDATE_MESSAGE_ENDING_FITS_PROTOCOL(rawMessage, messageSize)

    int8_t errorCode = validateMessageLengthInRange(messageSize);
    if (errorCode)
        return errorCode;

    errorCode = validateMessageChecksum(rawMessage, messageSize);
    if (errorCode)
        return errorCode;

    errorCode = validateMessageType(rawMessage);
    if (errorCode)
        return errorCode;

    return 0;
}

//endregion

//region Helper Functions Definition/Implementation

static int8_t validateMessageLengthInRange(size_t messageSize)
{
    if (messageSize <= MESSAGE_MIN_LENGTH)
    {
        if (messageSize < MESSAGE_MIN_LENGTH)
            return -ESHORT_MESSAGE;
        else
            return -EMISSING_MESSAGE_DATA;
    }
    else if (messageSize > MESSAGE_MAX_LENGTH)
        return -ELONG_MESSAGE;

    return EVALID;
}

static int8_t validateMessageType(const char *message)
{
    // Validate Talker-ID
    if (message[MESSAGE_TYPE_START_INDEX] != TALKER_PROPRIETARY_ID &&
        message[MESSAGE_TYPE_START_INDEX] != TALKER_GNSS_ID)
        return -EINVALID_MESSAGE_TYPE;

    if (message[MESSAGE_TYPE_START_INDEX] == TALKER_PROPRIETARY_ID)
    {
        // Check if message is too short or too long
        if (message[MESSAGE_DATA_START_MIN_INDEX] != PROTOCOL_FIELD_DELIMITER)
            return -EINVALID_MESSAGE_TYPE;

        // Talker ID consists of a single char, iterate exclusive
        for (int i = MESSAGE_TYPE_START_INDEX + 1; i < MESSAGE_DATA_START_MIN_INDEX; ++i)
        {
            if (!isalpha(message[i]))
                return -EINVALID_MESSAGE_TYPE;
        }
    }
    else
    {
        // Check if message is too short or too long
        if (message[MESSAGE_DATA_START_MAX_INDEX] != PROTOCOL_FIELD_DELIMITER)
            return -EINVALID_MESSAGE_TYPE;

        // Talker ID consists of 2 chars, iterate inclusive
        for (int i = MESSAGE_TYPE_START_INDEX + 1; i <= MESSAGE_DATA_START_MIN_INDEX; ++i)
        {
            if (!isalpha(message[i]))
                return -EINVALID_MESSAGE_TYPE;
        }
    }

    return EVALID;
}

//endregion
