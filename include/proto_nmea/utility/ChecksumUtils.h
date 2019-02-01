//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMUTILS_H
#define PROTO_NMEA_CHECKSUMUTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "GlobalUtils.h"

int calculateChecksum(const char *begin, const char *end);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_CHECKSUMUTILS_H
