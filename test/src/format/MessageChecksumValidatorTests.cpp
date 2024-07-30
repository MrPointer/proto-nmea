//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include <string>

#include "CatchSmartInclude.hpp"
#include "proto_nmea_test/fakes/FakeUtils.h"
#include "proto_nmea_test/fakes/format/ChecksumValidatorFakes.h"
#include "proto_nmea_test/fakes/format/ChecksumFormatValidatorFakes.h"
#include "proto_nmea_test/fakes/etc/checksum/ChecksumValueComparatorFakes.h"

#include <proto_nmea/format/checksum/MessageChecksumValidator.h>

SCENARIO("Message checksum validation handles invalid input (with mocks)", "[mock]")
{
    DISABLE_FAKE(validateMessageChecksum)

    GIVEN("Invalid checksum format")
    {
        int8_t fakeErrorCode;

        ENABLE_FFF_FAKE(validateChecksumFormat);

        ENABLE_FFF_FAKE(compareChecksumData)
        compareChecksumData_fake.return_val = 0;

        std::string message{"abc"};

        GIVEN("Invalid checksum error")
        {
            fakeErrorCode = -EUNEXPECTED_CHECKSUM_FORMAT;
            validateChecksumFormat_fake.return_val = fakeErrorCode;

            WHEN("Message checksum is validated")
            {
                auto result =
                        validateMessageChecksum(reinterpret_cast<const unsigned char *>(message.c_str()),
                                                message.size());

                THEN("Format validator's error is returned (forwarded)")
                {
                    REQUIRE(result == fakeErrorCode);
                }
            }
        }
        AND_GIVEN("Missing checksum data error")
        {
            fakeErrorCode = -EMISSING_CHECKSUM_DATA;
            validateChecksumFormat_fake.return_val = fakeErrorCode;

            WHEN("Message checksum is validated")
            {
                auto result =
                        validateMessageChecksum(reinterpret_cast<const unsigned char *>(message.c_str()),
                                                message.size());

                THEN("Format validator's error is returned (forwarded)")
                {
                    REQUIRE(result == fakeErrorCode);
                }
            }
        }
        AND_GIVEN("Missing checksum error")
        {
            fakeErrorCode = -EMISSING_CHECKSUM;
            validateChecksumFormat_fake.return_val = fakeErrorCode;

            WHEN("Message checksum is validated")
            {
                auto result =
                        validateMessageChecksum(reinterpret_cast<const unsigned char *>(message.c_str()),
                                                message.size());

                THEN("Format validator's error is returned (forwarded)")
                {
                    REQUIRE(result == fakeErrorCode);
                }
            }
        }
    }

    GIVEN("Wrong checksum value")
    {
        ENABLE_FFF_FAKE(validateChecksumFormat);
        validateChecksumFormat_fake.return_val = EVALID;

        ENABLE_FFF_FAKE(compareChecksumData)

        std::string message{"abc"};

        GIVEN("Actual checksum bigger than calculated")
        {
            compareChecksumData_fake.return_val = 1;

            WHEN("Message checksum is validated")
            {
                auto result =
                        validateMessageChecksum(reinterpret_cast<const unsigned char *>(message.c_str()),
                                                message.size());

                THEN("Wrong checksum error is returned (forwarded)")
                {
                    REQUIRE(result == -EWRONG_CHECKSUM);
                }
            }
        }
        AND_GIVEN("Checksum smaller than calculated")
        {
            compareChecksumData_fake.return_val = -1;

            WHEN("Message checksum is validated")
            {
                auto result =
                        validateMessageChecksum(reinterpret_cast<const unsigned char *>(message.c_str()),
                                                message.size());

                THEN("Wrong checksum error is returned (forwarded)")
                {
                    REQUIRE(result == -EWRONG_CHECKSUM);
                }
            }
        }
    }
}

SCENARIO("Message checksum validated correctly (with mocks)", "[mock]")
{
    DISABLE_FAKE(validateMessageChecksum)

    GIVEN("Valid checksum")
    {
        ENABLE_FFF_FAKE(validateChecksumFormat)
        validateChecksumFormat_fake.return_val = EVALID;

        ENABLE_FFF_FAKE(compareChecksumData)
        compareChecksumData_fake.return_val = 0;

        std::string message{"abc"};

        WHEN("Message checksum is validated")
        {
            auto result = validateMessageChecksum(reinterpret_cast<const unsigned char *>(message.c_str()),
                                                  message.size());

            THEN("Checksum format validator is called, and exactly once")
            {
                REQUIRE(validateChecksumFormat_fake.call_count == 1);
            }
            AND_THEN("Checksum value comparator is called, and exactly once")
            {
                REQUIRE(compareChecksumData_fake.call_count == 1);
            }
            AND_THEN("Valid result is returned")
            {
                REQUIRE(result == EVALID);
            }
        }
    }
}
