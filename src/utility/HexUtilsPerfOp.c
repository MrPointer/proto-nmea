//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/utility/HexUtils.h"

//region Hex Table

#if defined(__GNUC__)
static const uint8_t hexTable[] = {
        [0 ... 255] = -1, // bit aligned access into this table is considerably
        ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, // faster for most modern processors,
        ['A'] = 10, 11, 12, 13, 14, 15,       // for the space conscious, reduce to
        ['a'] = 10, 11, 12, 13, 14, 15        // signed char.
};
#else
static const uint8_t hexTable[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};
#endif

//endregion

uint32_t stringToHex(unsigned const char *hexString)
{
    uint32_t ret = 0;
    while (*hexString && ret >= 0)
    {
        ret = (ret << 4u) | hexTable[*hexString++];
    }
    return ret;
}

uint32_t substringToHex(unsigned const char *hexString, size_t startIndex, size_t length)
{
    uint32_t ret = 0;
    const size_t stopIndex = startIndex + length;

    for (size_t i = startIndex; i < stopIndex && hexString[i] && ret >= 0; ++i)
    {
        ret = (ret << 4u) | hexTable[hexString[i]];
    }
    return ret;
}

bool isHex(unsigned char c)
{
    return hexTable[c] != (unsigned char) (-1);
}
