//
// Created by timor on 04/08/2019.
//

#ifndef PROTO_NMEA_CHECKSUMVALIDATOR_H
#define PROTO_NMEA_CHECKSUMVALIDATOR_H

#include <stdint.h>
#include <string.h>

#include "ProtocolFormat.h"
#include "../Errors.h"

#include "../utility/ChecksumUtils.h"

int8_t validateChecksum(const unsigned char *message, size_t messageSize);

#endif //PROTO_NMEA_CHECKSUMVALIDATOR_H
