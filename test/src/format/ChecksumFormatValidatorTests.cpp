//
// Created by Timor Gruber on 09/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "CatchSmartInclude.hpp"
#include "proto_nmea_test/fakes/FakeUtils.h"

#include <string>

#include <proto_nmea/format/checksum/ChecksumFormatValidator.h>
#include "proto_nmea_test/fakes/format/ChecksumFormatValidatorFakes.h"

SCENARIO("Checksum format validation handles invalid input")
{
    DISABLE_FAKE(validateChecksumFormat)

    GIVEN("Invalid checksum format")
    {
        GIVEN("Unexpected delimiter position")
        {
            std::string checksum{"01"};

            WHEN("Delimiter is completely missing")
            {
                auto result =
                        validateChecksumFormat(reinterpret_cast<const unsigned char *>(checksum.c_str()));

                THEN("Missing-checksum error is returned")
                {
                    REQUIRE(result == -EMISSING_CHECKSUM);
                }
            }
            AND_WHEN("Delimiter is located at 2nd index")
            {
                checksum = "0";
                checksum += PROTOCOL_CHECKSUM_DELIMITER;
                checksum += "01";

                auto result =
                        validateChecksumFormat(reinterpret_cast<const unsigned char *>(checksum.c_str()));

                THEN("Missing-checksum error is returned")
                {
                    REQUIRE(result == -EMISSING_CHECKSUM);
                }
            }
        }
        GIVEN("Non-Hex data chars")
        {
            std::string checksum{PROTOCOL_CHECKSUM_DELIMITER};

            WHEN("All chars are invalid")
            {
                checksum += "xy";
                auto result =
                        validateChecksumFormat(reinterpret_cast<const unsigned char *>(checksum.c_str()));

                THEN("Unexpected-checksum-format error is returned")
                {
                    REQUIRE(result == -EUNEXPECTED_CHECKSUM_FORMAT);
                }
            }
            AND_WHEN("One of the chars is invalid")
            {
                WHEN("1st char is invalid")
                {
                    checksum += "x1";
                    auto result =
                            validateChecksumFormat(reinterpret_cast<const unsigned char *>(checksum.c_str()));

                    THEN("Unexpected-checksum-format error is returned")
                    {
                        REQUIRE(result == -EUNEXPECTED_CHECKSUM_FORMAT);
                    }
                }
                AND_WHEN("2nd char is invalid")
                {
                    checksum += "1y";
                    auto result =
                            validateChecksumFormat(reinterpret_cast<const unsigned char *>(checksum.c_str()));

                    THEN("Unexpected-checksum-format error is returned")
                    {
                        REQUIRE(result == -EUNEXPECTED_CHECKSUM_FORMAT);
                    }
                }
            }
        }
    }
}

SCENARIO("Checksum format validated correctly")
{
    GIVEN("Valid checksum format")
    {
        std::string checksum{PROTOCOL_CHECKSUM_DELIMITER};
        checksum += "01";

        WHEN("Format is validated")
        {
            auto result = validateChecksumFormat(reinterpret_cast<const unsigned char *>(checksum.c_str()));

            THEN("Valid result is returned")
            {
                REQUIRE(result == EVALID);
            }
        }
    }
}
