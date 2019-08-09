//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include <string>

#include "../CatchSmartInclude.hpp"
#include "../utility/TypeConversionUtils.hpp"
#include "../utility/fakes/FakeUtils.h"

#include <proto_nmea/format/FormatChecker.h>
#include "fakes/ChecksumValidatorFakes.h"

SCENARIO("Null messages are reported as error")
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

SCENARIO("Invalid protocol start chars are reported errors")
{
    GIVEN("Invalid protocol start char")
    {
        char invalid_char = '#';
        std::string message{invalid_char};

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

SCENARIO("Invalid protocol stop chars are reported as errors")
{
    GIVEN("Invalid protocol stop chars")
    {
        std::string stopChars{"ab"};
        std::string message{"$GPGGA,*12"}; // ToDo: Factory?

        message = message.append(stopChars);

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

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
    std::string message{PROTOCOL_START_CHAR};

    std::string messageEndChars{};
    messageEndChars = messageEndChars.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

    GIVEN("Message type shorter than minimum")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        message = message.append(1, TALKER_PROPRIETARY_ID).append(MESSAGE_TYPE_MIN_LENGTH - 2, 'a')
                         .append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a');
        message += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Message type longer than maximum")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        message = message.append(1, TALKER_GNSS_ID).append(MESSAGE_TYPE_MAX_LENGTH, 'a')
                         .append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        message += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Unknown Talker ID")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        message = message.append(MESSAGE_TYPE_MIN_LENGTH, 'a').append(1, PROTOCOL_FIELD_DELIMITER)
                         .append(10, 'a').append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        message += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Delimiter after protocol start char")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        message = message.append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        message += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Delimiter in the middle of Talker-ID")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        message = message.append(1, 'G').append(1, PROTOCOL_FIELD_DELIMITER)
                         .append(1, 'P').append(10, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        message += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Delimiter between Talker-ID and Message Type")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        message = message.append("GP").append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        message += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }

    GIVEN("Delimiter in the middle of Message Type")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        message = message.append("GPGG").append(1, PROTOCOL_FIELD_DELIMITER)
                         .append(1, 'A').append(10, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        message += messageEndChars;

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Message Type error is returned")
            {
                REQUIRE(errorCode == -EINVALID_MESSAGE_TYPE);
            }
        }
    }
}

/*SCENARIO("Invalid checksum data reported as error")
{
    std::string message{PROTOCOL_START_CHAR};

    std::string messageEndChars;
    messageEndChars = messageEndChars.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

    GIVEN("Valid checksum position without checksum data")
    {
        message = message.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(5, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER);
        message += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Missing Checksum Data error is returned")
            {
                REQUIRE(errorCode == -EMISSING_CHECKSUM_DATA);
            }
        }
    }

    GIVEN("Valid checksum position, invalid checksum data")
    {
        message = message.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("mn");
        message += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Invalid Checksum error is returned")
            {
                REQUIRE(errorCode == -EUNEXPECTED_CHECKSUM_FORMAT);
            }
        }
    }

    GIVEN("Valid checksum format, non-matching data")
    {
        message = message.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(10, 'a')
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append(intToHexString(0));
        message += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Wrong Checksum Data error is returned")
            {
                REQUIRE(errorCode == -EWRONG_CHECKSUM);
            }
        }
    }
}*/

SCENARIO("Data-less messages are reported as errors")
{
    GIVEN("Message without data")
    {
        std::string message{PROTOCOL_START_CHAR};

        std::string nmeaMessageEnd;
        nmeaMessageEnd = nmeaMessageEnd.append(1, PROTOCOL_STOP_CHAR_1).append(1, PROTOCOL_STOP_CHAR_2);

        message = message.append("PGGA").append(1, PROTOCOL_FIELD_DELIMITER)
                         .append(1, PROTOCOL_CHECKSUM_DELIMITER).append("12");
        message += nmeaMessageEnd;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Missing Checksum Data error is returned")
            {
                REQUIRE(errorCode == -EMISSING_MESSAGE_DATA);
            }
        }
    }
}

SCENARIO("Validating format of valid messages (with mocks)", "[mock]")
{
    GIVEN("Valid NMEA message")
    {
        ENABLE_FFF_FAKE(validateMessageChecksum)
        validateMessageChecksum_fake.return_val = EVALID;

        std::string message{PROTOCOL_START_CHAR};
        std::string messageEndChars;

        messageEndChars = messageEndChars.append(1, PROTOCOL_STOP_CHAR_1)
                                         .append(1, PROTOCOL_STOP_CHAR_2);

        message = message.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(5, 'a');

        int messageChecksum = 0x01;
        message = message.append(1, PROTOCOL_CHECKSUM_DELIMITER).append(intToHexString(messageChecksum));

        message += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Valid format is returned")
            {
                REQUIRE(errorCode == EVALID);
            }
        }
    }
}

/*SCENARIO("Valid messages are reported as valid")
{
    GIVEN("Valid NMEA message")
    {
        std::string message{PROTOCOL_START_CHAR};
        std::string messageEndChars;

        messageEndChars = messageEndChars.append(1, PROTOCOL_STOP_CHAR_1)
                                         .append(1, PROTOCOL_STOP_CHAR_2);

        message = message.append("GPGGA").append(1, PROTOCOL_FIELD_DELIMITER).append(5, 'a');

        // Checksum of the message above - Has been calculated by 3rd party tool to avoid dependency between units
        int messageChecksum = 0x1b;
        message = message.append(1, PROTOCOL_CHECKSUM_DELIMITER).append(intToHexString(messageChecksum));

        message += messageEndChars;

        WHEN("Message is validated")
        {
            int8_t errorCode = validateMessageFormat(message.c_str());

            THEN("Valid format is returned")
            {
                REQUIRE(errorCode == -EVALID);
            }
        }
    }
}*/
