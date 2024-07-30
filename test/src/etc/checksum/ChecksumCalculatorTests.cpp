//
// Created by Timor Gruber on 10/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "CatchSmartInclude.hpp"
#include <fff.h>
#include "proto_nmea_test/fakes/FakeUtils.h"
#include "proto_nmea_test/fakes/etc/checksum/ChecksumXORCalculatorFakes.h"

#include <string>

#include <proto_nmea/etc/checksum/ChecksumCalculator.h>

SCENARIO("XOR range checksum calculation handles invalid input")
{
    DISABLE_FAKE(calculateRangeChecksum)

    GIVEN("Null begin string")
    {
        AND_GIVEN("Non-Empty end string")
        {
            std::string str{"abc"};

            WHEN("Checksum is calculated")
            {
                auto result = calculateRangeChecksum(nullptr,
                                                     reinterpret_cast<const unsigned char *>(str.c_str()));

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
        AND_GIVEN("Empty end string")
        {
            std::string str;

            WHEN("Checksum is calculated")
            {
                auto result = calculateRangeChecksum(nullptr,
                                                     reinterpret_cast<const unsigned char *>(str.c_str()));

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
    }

    GIVEN("Null end string")
    {
        AND_GIVEN("Non-Empty begin string")
        {
            std::string str{"abc"};

            WHEN("Checksum is calculated")
            {
                auto result = calculateRangeChecksum(reinterpret_cast<const unsigned char *>(str.c_str()),
                                                     nullptr);

                THEN("Result is not zero")
                {
                    REQUIRE(result != 0);
                }
            }
        }
        AND_GIVEN("Empty beginning string")
        {
            std::string str;

            WHEN("Checksum is calculated")
            {
                auto result = calculateRangeChecksum(reinterpret_cast<const unsigned char *>(str.c_str()),
                                                     nullptr);

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
    }

    GIVEN("Both begin & end strings are null")
    {
        WHEN("Checksum is calculated")
        {
            auto result = calculateRangeChecksum(nullptr, nullptr);

            THEN("Result is zero")
            {
                REQUIRE(result == 0);
            }
        }
    }
}

SCENARIO("XOR range checksum calculated correctly")
{
    DISABLE_FAKE(calculateRangeChecksum)

    GIVEN("Both range edges are empty")
    {
        std::string beginStr, endStr;

        WHEN("Checksum is calculated")
        {
            auto result = calculateRangeChecksum(reinterpret_cast<const unsigned char *>(beginStr.c_str()),
                                                 reinterpret_cast<const unsigned char *>(endStr.c_str()));

            THEN("Result is zero")
            {
                REQUIRE(result == 0);
            }
        }
    }

    GIVEN("Some ASCII string")
    {
        std::string str{"abc"};

        WHEN("Range consists of entire string")
        {
            const int expectedChecksum = 0x60; // Calculated by 'ScadaCore' - 3rd-Party calculator

            AND_WHEN("Checksum is calculated")
            {
                auto result = calculateRangeChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin()),
                        reinterpret_cast<const unsigned char *>(str._Unchecked_end()));

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
        }
        WHEN("Range consists of first 2 elements of the string")
        {
            const int expectedChecksum = 0x03; // Calculated by 'ScadaCore' - 3rd-Party calculator

            AND_WHEN("Checksum is calculated")
            {
                auto result = calculateRangeChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin()),
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin() + 2));

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
        }
        WHEN("Range consists of last 2 elements of the string")
        {
            const int expectedChecksum = 0x01; // Calculated by 'ScadaCore' - 3rd-Party calculator

            AND_WHEN("Checksum is calculated")
            {
                auto result = calculateRangeChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_end() - 2),
                        reinterpret_cast<const unsigned char *>(str._Unchecked_end()));

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
        }
    }
}

SCENARIO("XOR length checksum calculation handles invalid input")
{
    DISABLE_FAKE(calculateLengthChecksum)

    GIVEN("Null string")
    {
        AND_GIVEN("Zero length")
        {
            std::string str;

            WHEN("Checksum is calculated")
            {
                auto result = calculateLengthChecksum(nullptr, 0);

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
        AND_GIVEN("Non-zero length")
        {
            std::string str{"abc"};

            WHEN("Checksum is calculated")
            {
                auto result = calculateLengthChecksum(nullptr, str.length());

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
    }
}

SCENARIO("XOR length checksum calculated correctly")
{
    DISABLE_FAKE(calculateLengthChecksum)

    GIVEN("Zero length")
    {
        AND_GIVEN("Non-Empty string")
        {
            std::string str{"abc"};

            WHEN("Checksum is calculated")
            {
                auto result = calculateLengthChecksum(reinterpret_cast<const unsigned char *>(str.c_str()),
                                                      0);

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
        AND_GIVEN("Empty string")
        {
            std::string str;

            WHEN("Checksum is calculated")
            {
                auto result = calculateLengthChecksum(reinterpret_cast<const unsigned char *>(str.c_str()),
                                                      0);

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
    }

    GIVEN("Some ASCII string")
    {
        std::string str{"abc"};

        WHEN("Range consists of entire string")
        {
            const int expectedChecksum = 0x60; // Calculated by 'ScadaCore' - 3rd-Party calculator

            AND_WHEN("Checksum is calculated")
            {
                auto result = calculateLengthChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin()),
                        str.length());

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
        }
        WHEN("Range consists of first 2 elements of the string")
        {
            const int expectedChecksum = 0x03; // Calculated by 'ScadaCore' - 3rd-Party calculator

            AND_WHEN("Checksum is calculated")
            {
                auto result = calculateLengthChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin()),
                        2);

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
        }
        WHEN("Range consists of last 2 elements of the string")
        {
            const int expectedChecksum = 0x01; // Calculated by 'ScadaCore' - 3rd-Party calculator

            AND_WHEN("Checksum is calculated")
            {
                auto result = calculateLengthChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_end() - 2),
                        2);

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
        }
    }
}

SCENARIO("XOR full checksum calculation handles invalid input")
{
    DISABLE_FAKE(calculateChecksum)

    GIVEN("Null string")
    {
        WHEN("Checksum is calculated")
        {
            auto result = calculateChecksum(nullptr);

            THEN("Result is zero")
            {
                REQUIRE(result == 0);
            }
        }
    }
}

SCENARIO("XOR full checksum calculated correctly")
{
    DISABLE_FAKE(calculateChecksum)

    GIVEN("Empty string")
    {
        std::string str;

        WHEN("Checksum is calculated")
        {
            auto result = calculateChecksum(reinterpret_cast<const unsigned char *>(str.c_str()));

            THEN("Result is zero")
            {
                REQUIRE(result == 0);
            }
        }
    }

    GIVEN("Some ASCII string")
    {
        std::string str{"abc"};
        const int expectedChecksum = 0x60; // Calculated by 'ScadaCore' - 3rd-Party calculator

        AND_WHEN("Checksum is calculated")
        {
            auto result = calculateChecksum(reinterpret_cast<const unsigned char *>(str.c_str()));

            THEN("Result is the XOR-8 of all elements in range")
            {
                REQUIRE(result == expectedChecksum);
            }
        }
    }
}
