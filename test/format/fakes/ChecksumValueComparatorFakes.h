//
// Created by Timor Gruber on 08/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMVALUECOMPARATORFAKES_H
#define PROTO_NMEA_CHECKSUMVALUECOMPARATORFAKES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <fff.h>
#include <proto_nmea/format/checksum/ChecksumValueComparator.h>

DECLARE_FAKE_VALUE_FUNC(int, compareChecksumData, const unsigned char*, unsigned int)

#ifdef __cplusplus
}
#endif
#endif //PROTO_NMEA_CHECKSUMVALUECOMPARATORFAKES_H
