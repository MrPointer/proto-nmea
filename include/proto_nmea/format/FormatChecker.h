//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_FORMATCHECKER
#define PROTO_NMEA_FORMATCHECKER

#include <inttypes.h>
#include <string.h>

#include "../Errors.h"
#include "ProtocolFormat.h"

#ifdef __cplusplus
extern "C"
{
#endif

int8_t validateMessageFormat(const char *rawMessage);

#ifdef __cplusplus
}
#endif

#endif
