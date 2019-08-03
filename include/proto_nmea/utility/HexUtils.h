//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_HEXUTILS_H
#define PROTO_NMEA_HEXUTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "../Errors.h"

/**
 * @brief Convert a hexadecimal string to a signed int
 * Works only with unsigned/positive numbers.
 *
 * @param hexString without decoration, case insensitive.
 *
 * @return -1 on error, or result (max (sizeof(long)*8)-1 bits)
 */
uint32_t stringToHex(unsigned const char *hexString);

/**
 * Checks whether given char represents a valid hexadecimal value.
 * @param c Character to check
 * @return True if char represents a valid hexadecimal value, false otherwise.
 */
bool isHex(char c);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_HEXUTILS_H
