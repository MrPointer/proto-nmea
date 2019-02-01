//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_PRESENTATIONUTILS_HPP
#define PROTO_NMEA_PRESENTATIONUTILS_HPP

#include <string>
#include <sstream>

template<typename T>
std::string intToHexString(T value)
{
    std::stringstream stream;
    stream << std::hex << value;
    return stream.str();
}

#endif //PROTO_NMEA_PRESENTATIONUTILS_HPP
