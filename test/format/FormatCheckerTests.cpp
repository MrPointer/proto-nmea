//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "../CatchSmartInclude.hpp"
#include <string>
#include <iostream>

#include "../utility/TypeConversionUtils.hpp"

#include <proto_nmea/format/FormatChecker.h>

SCENARIO("Null message is validated and considered general error")
{
    GIVEN("Null message")
    {
        std::string nullMessage{};
        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nullMessage.c_str());

            THEN("General error message is returned")
            {
                REQUIRE(errorCode == -ENULL_STRING);
            }
        }
    }
}

SCENARIO("Invalid protocol start chars are validated and considered errors")
{
    GIVEN("Invalid protocol start char")
    {
        char invalid_char = '#';
        std::string message{1, invalid_char};

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid protocol beginning error returned")
            {
                REQUIRE(errorCode == -EINVALID_PROTOCOL_BEGINNING);
            }
        }
    }
}

SCENARIO("Invalid protocol stop chars are validated and considered errors")
{
    GIVEN("Invalid protocol stop chars")
    {
        std::string stopChars{"ab"};
        std::string nmeaMessage{"$GPGGA,*12"};

        nmeaMessage = nmeaMessage.append(stopChars);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid protocol ending error returned")
            {
                REQUIRE(errorCode == -EINVALID_PROTOCOL_ENDING);
            }
        }
    }

    GIVEN("Valid 1st stop char")
    {
        std::string stopChars{PROTOCOL_STOP_CHAR_1};
        std::string nmeaMessage{"$GPGGA,*12"};

        stopChars = stopChars.append("a");
        nmeaMessage = nmeaMessage.append(stopChars);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid protocol ending error returned")
            {
                REQUIRE(errorCode == -EINVALID_PROTOCOL_ENDING);
            }
        }
    }
}

SCENARIO("Invalid message lengths are reported as errors")
{
    GIVEN("Message shorter than minimum")
    {
        std::string shortMessage{PROTOCOL_START_CHAR};
        shortMessage = shortMessage.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(shortMessage.c_str());

            THEN("Short Message error is returned")
            {
                REQUIRE(errorCode == -ESHORT_MESSAGE);
            }
        }
    }
    GIVEN("Message longer than maximum")
    {
        std::string longMessage{PROTOCOL_START_CHAR};
        longMessage = longMessage.append(MESSAGE_MAX_LENGTH, 'a');
        longMessage = longMessage.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(longMessage.c_str());

            THEN("Long Message error is returned")
            {
                REQUIRE(errorCode == -ELONG_MESSAGE);
            }
        }
    }
}

SCENARIO("Invalid message types are reported as errors")
{
    std::string nmeaMessage{PROTOCOL_START_CHAR};
    std::string messageEndChars{};

    messageEndChars = messageEndChars.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

    GIVEN("Delimiter after protocol start char")
    {
        nmeaMessage = nmeaMessage.append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a')
                .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        nmeaMessage += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Delimiter in the middle of Talker-ID")
    {
        nmeaMessage = nmeaMessage.append(1, 'G').append(1, PROTOCOL_FIELD_DELIMITER).append(1, 'P').append(10, 'a')
                .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        nmeaMessage += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Delimiter between Talker-ID and Message Type")
    {
        nmeaMessage = nmeaMessage.append("GP").append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a')
                .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        nmeaMessage += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Delimiter in the middle of Message Type")
    {
        nmeaMessage = nmeaMessage.append("GPGG").append(1, PROTOCOL_FIELD_DELIMITER).append(1, 'A').append(10, 'a')
                .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        nmeaMessage += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }
}

SCENARIO("Invalid checksum data reported as error")
{
    std::string messageEndChars;
    messageEndChars = messageEndChars.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

    GIVEN("Valid checksum position without checksum data")
    {
        std::string nmeaMessage{PROTOCOL_START_CHAR};

        nmeaMessage = nmeaMessage.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(5, 'a')
                .append(1, PROTOCOL_CHECKSUM_DELIMITER);
        nmeaMessage += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Missing Checksum Data error is returned")
            {
                REQUIRE(errorCode == -EMISSING_CHECKSUM_DATA);
            }
        }
    }

    GIVEN("Valid checksum format, non-matching data")
    {
        std::string nmeaMessage{PROTOCOL_START_CHAR};

        size_t numberOfDataChars = 12;

        nmeaMessage = nmeaMessage.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(numberOfDataChars, 'a')
                .append(1, PROTOCOL_CHECKSUM_DELIMITER).append(std::to_string(numberOfDataChars));
        nmeaMessage += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Wrong Checksum Data error is returned")
            {
                REQUIRE(errorCode == -EWRONG_CHECKSUM);
            }
        }
    }
}

SCENARIO("Data-less messages are reported as errors")
{
    GIVEN("Message without data")
    {
        std::string nmeaMessage{PROTOCOL_START_CHAR};
        std::string nmeaMessageEnd;

        nmeaMessageEnd = nmeaMessageEnd.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

        nmeaMessage = nmeaMessage.append("PGGA").append(1, PROTOCOL_FIELD_DELIMITER)
                .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        nmeaMessage += nmeaMessageEnd;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Missing Checksum Data error is returned")
            {
                REQUIRE(errorCode == -EMISSING_MESSAGE_DATA);
            }
        }
    }
}

SCENARIO("Valid messages are reported as valid")
{
    GIVEN("Valid NMEA message")
    {
        std::string nmeaMessage{PROTOCOL_START_CHAR};
        std::string messageEndChars;

        messageEndChars = messageEndChars.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

        nmeaMessage = nmeaMessage.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(5, 'a');

        // Checksum of the message above - Has been calculated by 3rd party tool to avoid dependency between units
        int messageChecksum = 0x1b;

        nmeaMessage = nmeaMessage.append(1, PROTOCOL_CHECKSUM_DELIMITER)
                .append(intToHexString(messageChecksum));

        nmeaMessage += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Valid format is returned")
            {
                REQUIRE(errorCode == -EVALID);
            }
        }
    }
}
