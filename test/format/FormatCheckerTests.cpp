//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include <catch/catch.hpp>
#include <iostream>

#include <proto_nmea/format/FormatChecker.h>

SCENARIO("Invalid chars are considered errors")
{
    GIVEN("Invalid protocol start char")
    {
        char invalid_char = '#';
        std::string nmeaMessage{1, invalid_char};

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Start-Char error returned")
            {
                REQUIRE(errorCode == -EINVALID_PROTOCOL_START);
            }
        }
    }
}

SCENARIO("Misplaced delimiters are considered errors")
{
    std::string nmeaMessage{PROTOCOL_START_CHAR};

    GIVEN("Delimiter after protocol start char")
    {
        nmeaMessage = nmeaMessage.append(1, PROTOCOL_FIELD_DELIMITER);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Start-Char error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }

    GIVEN("Delimiter in the middle of Talker-ID")
    {
        nmeaMessage = nmeaMessage.append(1, 'G').append(1, PROTOCOL_FIELD_DELIMITER).append(1, 'P');

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Start-Char error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }

    GIVEN("Delimiter between Talker-ID and Message Type")
    {
        nmeaMessage = nmeaMessage.append("GP").append(1, PROTOCOL_FIELD_DELIMITER);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Start-Char error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }

    GIVEN("Delimiter in the middle of Message Type")
    {
        nmeaMessage = nmeaMessage.append("GPGG").append(1, PROTOCOL_FIELD_DELIMITER).append(1, 'A');

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Start-Char error returned")
            {
                REQUIRE(errorCode == -EMISPLACED_DELIMITER);
            }
        }
    }
}
