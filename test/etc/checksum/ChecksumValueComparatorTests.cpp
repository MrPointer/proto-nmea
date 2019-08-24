//
// Created by Timor Gruber on 23/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "../../CatchSmartInclude.hpp"
#include <fff.h>
#include "../../utility/fakes/FakeUtils.h"
#include "fakes/ChecksumValueComparatorFakes.h"

#include <string>

#include <proto_nmea/etc/checksum/ChecksumValueComparator.h>

SCENARIO("Checksum value-comparator handles invalid input")
{
    GIVEN("Null checksum string")
    {
        DISABLE_FAKE(compareChecksumData)

        std::string checksum;

        WHEN("Value is compared")
        {
            auto result = compareChecksumData(reinterpret_cast<const unsigned char *>(checksum.c_str()),
                                              0);

            THEN("Result is non-zero (Unequal)")
            {
                REQUIRE(result != 0);
            }
        }
    }
}

SCENARIO("Checksum value-comparator compares successfully")
{
    GIVEN("Checksum string")
    {
        DISABLE_FAKE(compareChecksumData)

        std::string checksum{"ab"}; // Must be 2 chars

        AND_GIVEN("Invalid calculated checksum value")
        {
            const int calculatedChecksum = 0x01;

            WHEN("Checksum is compared")
            {
                auto result = compareChecksumData(reinterpret_cast<const unsigned char *>(checksum.c_str()),
                                                  calculatedChecksum);
                THEN("Result is non-zero (Unequal)")
                {
                    REQUIRE(result != 0);
                }
            }
        }
        AND_GIVEN("Valid calculated checksum value")
        {
            const int calculatedChecksum = 0xAB;

            WHEN("Checksum is compared")
            {
                auto result = compareChecksumData(reinterpret_cast<const unsigned char *>(checksum.c_str()),
                                                  calculatedChecksum);
                THEN("Result is zero (Equal)")
                {
                    REQUIRE(result == 0);
                }
            }
        }
    }
}
