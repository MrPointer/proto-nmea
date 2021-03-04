//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_TYPECONVERSIONUTILS_HPP
#define PROTO_NMEA_TYPECONVERSIONUTILS_HPP

#include <string>
#include <sstream>
#include <iomanip>

/**
 * Converts an int to a string representing its' hex value, prepending it with the requested width.
 * @tparam T Any decimal type which can be represented as a hex value of itself.
 * @param value The actual value of **T** to convert.
 * @param width String's final width, padded with zeros as necessary.
 * e.g. For the value 1 and width of 2, the resulting string would be '01'.
 * @return Possibly zero-padded string representing the hex value of the given input decimal.
 */
template<typename T>
std::string intToHexString(T value, int width = 2)
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(width) << std::hex << value;
    return stream.str();
}

#endif //PROTO_NMEA_TYPECONVERSIONUTILS_HPP
