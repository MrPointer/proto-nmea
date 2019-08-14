//
// Created by Timor Gruber on 10/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "../../CatchSmartInclude.hpp"
#include <fff.h>

#include <string>

#include <proto_nmea/etc/checksum/ChecksumCalculator.h>

SCENARIO("Checksum (XOR) calculated correctly")
{
    GIVEN("Zero-length string")
    {
        std::string str;

        WHEN("Range-based calculation is performed")
        {
            auto result = calculateRangeChecksum(reinterpret_cast<const unsigned char *>(str.c_str()),
                                                 nullptr);

            THEN("Result is zero")
            {
                REQUIRE(result == 0);
            }
        }
    }

    GIVEN("Some ASCII string")
    {
        std::string str{"abc"};

        WHEN("Range-based calculation is performed")
        {
            AND_WHEN("Range consists of entire string")
            {
                const int expectedChecksum = 0x60; // Calculated by 'ScadaCore' - 3rd-Party calculator
                auto result = calculateRangeChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin()),
                        reinterpret_cast<const unsigned char *>(str._Unchecked_end()));

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
            AND_WHEN("Range consists of first 2 elements of the string")
            {
                const int expectedChecksum = 0x03; // Calculated by 'ScadaCore' - 3rd-Party calculator
                auto result = calculateRangeChecksum(
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin()),
                        reinterpret_cast<const unsigned char *>(str._Unchecked_begin() + 2));

                THEN("Result is the XOR-8 of all elements in range")
                {
                    REQUIRE(result == expectedChecksum);
                }
            }
            AND_WHEN("Range consists of last 2 elements of the string")
            {
                const int expectedChecksum = 0x01; // Calculated by 'ScadaCore' - 3rd-Party calculator
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

SCENARIO("Checksum (XOR) calculator handles invalid input")
{
    GIVEN("Null string")
    {
        WHEN("Range-based calculation is performed")
        {
            AND_WHEN("Beginning edge is null")
            {
                GIVEN("Non-Empty ending string")
                {
                    std::string str{"abc"};
                    auto result = calculateRangeChecksum(nullptr,
                                                         reinterpret_cast<const unsigned char *>(
                                                                 str.c_str()));

                    THEN("Result is zero")
                    {
                        REQUIRE(result == 0);
                    }
                }
                GIVEN("Empty ending string")
                {
                    std::string str;
                    auto result = calculateRangeChecksum(nullptr,
                                                         reinterpret_cast<const unsigned char *>(
                                                                 str.c_str()));

                    THEN("Result is zero")
                    {
                        REQUIRE(result == 0);
                    }
                }
            }
            AND_WHEN("Ending edge is null")
            {
                GIVEN("Non-Empty beginning string")
                {
                    std::string str{"abc"};
                    auto result = calculateRangeChecksum(reinterpret_cast<const unsigned char *>(str.c_str()),
                                                         nullptr);

                    THEN("Result is not zero")
                    {
                        REQUIRE(result != 0);
                    }
                }
                GIVEN("Empty beginning string")
                {
                    std::string str;
                    auto result = calculateRangeChecksum(reinterpret_cast<const unsigned char *>(str.c_str()),
                                                         nullptr);

                    THEN("Result is zero")
                    {
                        REQUIRE(result == 0);
                    }
                }
            }
            AND_WHEN("Both edges are null")
            {
                auto result = calculateRangeChecksum(nullptr, nullptr);

                THEN("Result is zero")
                {
                    REQUIRE(result == 0);
                }
            }
        }
    }
}
