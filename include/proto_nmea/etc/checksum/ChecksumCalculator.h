//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMCALCULATOR_H
#define PROTO_NMEA_CHECKSUMCALCULATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "proto_nmea/utility/StringUtils.h"
#include "proto_nmea/utility/HexUtils.h"

/**
 * @brief Calculates checksum over the given range.
 * @param begin Beginning of the range to calculate checksum on
 * @param end Ending of the range to calculate checksum on
 * @return Calculated checksum
 */
uint32_t calculateRangeChecksum(const unsigned char *begin, const unsigned char *end);

/**
 * @brief Calculates checksum over the given string, taking length chars into account.
 * @param str String to calculate checksum on
 * @param length Length of the string to calculate. May be less than entire string's length.
 * @return Calculated checksum
 */
inline uint32_t calculateLengthChecksum(const unsigned char *str, size_t length)
{ return calculateRangeChecksum(str, str + length); }

/**
* @brief Calculates checksum over the entire given string, i.e. until Null-Char ('\0') is met.
* @param str String to calculate checksum on
* @return Calculated checksum
*/
inline uint32_t calculateChecksum(const unsigned char *str)
{ return calculateRangeChecksum(str, NULL); }


#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_CHECKSUMCALCULATOR_H
