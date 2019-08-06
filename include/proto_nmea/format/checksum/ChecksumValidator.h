//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMVALIDATOR_H
#define PROTO_NMEA_CHECKSUMVALIDATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>

#include "proto_nmea/format/ProtocolFormat.h"
#include "proto_nmea/Errors.h"

#include "proto_nmea/utility/StringUtils.h"
#include "proto_nmea/utility/ChecksumUtils.h"

#ifdef UNIT_TEST

int8_t validateChecksum_testWrapper(const unsigned char *buffer, unsigned int calculatedChecksum);

#endif

int8_t validateChecksum(const unsigned char *buffer, unsigned int calculatedChecksum);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_CHECKSUMVALIDATOR_H
