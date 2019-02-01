//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_GLOBALUTILS_H
#define PROTO_NMEA_GLOBALUTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>
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
int stringToHex(unsigned const char *hexString);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_GLOBALUTILS_H
