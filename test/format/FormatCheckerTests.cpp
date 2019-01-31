//
// Copyright (c) 2019 Takpit. All rights reserved.
//

//region Catch include
#ifdef CATCH_SYSTEM_PACKAGE

#include <catch2/catch.hpp>

#else
#include <catch.hpp>
#endif
//endregion

#include <iostream>

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
        std::string nmeaMessage{1, invalid_char};

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

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

SCENARIO("Misplaced delimiters are validated and considered errors")
{
    std::string nmeaMessage{PROTOCOL_START_CHAR};
    std::string messageStopChars{};

    messageStopChars = messageStopChars.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

    GIVEN("Delimiter after protocol start char")
    {
        nmeaMessage = nmeaMessage.append(1, PROTOCOL_FIELD_DELIMITER).append("abcdefghij");
        nmeaMessage = nmeaMessage.append(messageStopChars);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Misplaced delimiter error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }

    GIVEN("Delimiter in the middle of Talker-ID")
    {
        nmeaMessage = nmeaMessage.append(1, 'G').append(1, PROTOCOL_FIELD_DELIMITER).append(1, 'P')
                .append("abcdefghij");
        nmeaMessage = nmeaMessage.append(messageStopChars);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Misplaced delimiter error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }

    GIVEN("Delimiter between Talker-ID and Message Type")
    {
        nmeaMessage = nmeaMessage.append("GP").append(1, PROTOCOL_FIELD_DELIMITER).append("abcdefghij");
        nmeaMessage = nmeaMessage.append(messageStopChars);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Misplaced delimiter error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }

    GIVEN("Delimiter in the middle of Message Type")
    {
        nmeaMessage = nmeaMessage.append("GPGG").append(1, PROTOCOL_FIELD_DELIMITER).append(1, 'A')
                .append("abcdefghij");
        nmeaMessage = nmeaMessage.append(messageStopChars);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Misplaced delimiter error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }
}

SCENARIO("Invalid message lengths are reported as errors")
{
    GIVEN("Message shorter than minimum")
    {
        std::string shortNmeaMessage{PROTOCOL_START_CHAR};
        shortNmeaMessage = shortNmeaMessage.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);
        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(shortNmeaMessage.c_str());
            THEN("Short Message error is returned")
            {
                REQUIRE(errorCode == -ESHORT_MESSAGE);
            }
        }
    }
    GIVEN("Message longer than maximum")
    {
        std::string longMessage{PROTOCOL_START_CHAR};
        for (int i = 0; i < MESSAGE_MAX_LENGTH; ++i)
        {
            longMessage += "1";
        }
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
