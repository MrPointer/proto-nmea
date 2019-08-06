//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_MESSAGECHECKSUMVALIDATOR_H
#define PROTO_NMEA_MESSAGECHECKSUMVALIDATOR_H

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

int8_t validateMessageChecksum_testWrapper(const unsigned char *message, size_t messageSize);

#endif

int8_t validateMessageChecksum(const unsigned char *message, size_t messageSize);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_MESSAGECHECKSUMVALIDATOR_H
