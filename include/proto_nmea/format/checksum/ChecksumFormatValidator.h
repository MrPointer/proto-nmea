//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMFORMATVALIDATOR_H
#define PROTO_NMEA_CHECKSUMFORMATVALIDATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>

#include "../ProtocolFormat.h"
#include "../../Errors.h"
#include "../../utility/HexUtils.h"

int8_t validateChecksumFormat(const unsigned char *checksumString);

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_CHECKSUMFORMATVALIDATOR_H
