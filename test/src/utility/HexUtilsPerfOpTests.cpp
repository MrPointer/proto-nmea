//
// Created by Timor Gruber on 25/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "CatchSmartInclude.hpp"

#include <proto_nmea/utility/HexUtils.h>

SCENARIO("Hex strings can be converted to matching integers")
{
    GIVEN("Valid Hex-String")
    {
        const unsigned char hexString[3] = "ab";
        const uint32_t expectedInt = 0xab;

        WHEN("String is converted")
        {
            auto result = stringToHex(hexString);

            THEN("Result is the matching hex integer")
            {
                REQUIRE(result == expectedInt);
            }
        }
    }
}

SCENARIO("Hex substrings can be converted to matching integers")
{
    GIVEN("Valid Hex Substring")
    {
        const unsigned char string[5] = "0ab1";
        const size_t hexStringStartIndex = 1;
        const size_t hexStringLength = 2;
        const uint32_t expectedInt = 0xab;

        WHEN("String is converted")
        {
            auto result = substringToHex(string, hexStringStartIndex, hexStringLength);

            THEN("Result is the matching hex integer")
            {
                REQUIRE(result == expectedInt);
            }
        }
    }
}

SCENARIO("Chars can be correctly identified as hex")
{
    GIVEN("Non-Hex char")
    {
        unsigned char c = 'x';

        WHEN("Char is checked")
        {
            auto result = isHex(c);

            THEN("Result is false")
            {
                REQUIRE_FALSE(result);
            }
        }
    }

    GIVEN("Hex char")
    {
        unsigned char c = 'a';

        WHEN("Char is checked")
        {
            auto result = isHex(c);

            THEN("Result is True")
            {
                REQUIRE(result);
            }
        }
    }
}