//
// Created by Timor Gruber on 15/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMXORCALCULATORFAKES_H
#define PROTO_NMEA_CHECKSUMXORCALCULATORFAKES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <fff.h>
#include <proto_nmea/etc/checksum/ChecksumCalculator.h>

DECLARE_FAKE_VALUE_FUNC(uint32_t, calculateRangeChecksum, const unsigned char *, const unsigned char *)

DECLARE_FAKE_VALUE_FUNC(uint32_t, calculateLengthChecksum, const unsigned char *, size_t)

DECLARE_FAKE_VALUE_FUNC(uint32_t, calculateChecksum, const unsigned char *)

#ifdef __cplusplus
}
#endif
#endif //PROTO_NMEA_CHECKSUMXORCALCULATORFAKES_H
