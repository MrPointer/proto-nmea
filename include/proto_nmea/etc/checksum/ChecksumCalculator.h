//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMCALCULATOR_H
#define PROTO_NMEA_CHECKSUMCALCULATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "proto_nmea/utility/HexUtils.h"

uint32_t calculateChecksum(const unsigned char *begin, const unsigned char *end);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_CHECKSUMCALCULATOR_H
