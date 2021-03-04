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
#include <string.h>

#include "../Errors.h"

/**
 * @brief Converts a given hexadecimal string to a signed int
 * Works only with unsigned/positive numbers.
 *
 * @param hexString String representing a hex-value, case insensitive
 *
 * @return -1 on error, or result.
 */
uint32_t stringToHex(unsigned const char *hexString);

/**
 * @brief Converts a substring of a given hexadecimal string to a signed int
 * Works only with unsigned/positive numbers.
 *
 * @param hexString String representing a hex-value, case insensitive
 * @param startIndex Index to take substring from
 * @param length Length of the substring
 *
 * @return -1 on error, or result.
 */
uint32_t substringToHex(unsigned const char *hexString, size_t startIndex, size_t length);

/**
 * Checks whether given char represents a valid hexadecimal value
 * @param c Character to check
 * @return True if char represents a valid hexadecimal value, false otherwise
 */
bool isHex(unsigned char c);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_HEXUTILS_H
