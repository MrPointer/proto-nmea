#include <catch/catch.hpp>

#include <proto_nmea/format_checker/formatChecker.h>

SCENARIO("Invalid chars are handled as errors")
{
    GIVEN("Invalid protocol start char")
    {
        char invalid_char = '#';
        std::string nmeaMessage{invalid_char};

        WHEN("Message format is validated")
        {
            int8_t errorCode = validateMessageFormat(nmeaMessage.c_str());

            THEN("Invalid Start-Char error returned")
            {
                REQUIRE(errorCode == -EINVAL_NMEA_MESSAGE_START);
            }
        }
    }
}
