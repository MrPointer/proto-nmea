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

#include "ProtocolFormat.h"
#include "../Errors.h"

#include "../utility/StringUtils.h"
#include "../utility/ChecksumUtils.h"

#ifdef UNIT_TEST

int8_t validateChecksum_testWrapper(const unsigned char *message, size_t messageSize);

#endif

int8_t validateChecksum(const unsigned char *message, size_t messageSize);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_CHECKSUMVALIDATOR_H
