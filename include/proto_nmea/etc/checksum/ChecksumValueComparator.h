//
// Created by Timor Gruber on 08/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_CHECKSUMVALUECOMPARATOR_H
#define PROTO_NMEA_CHECKSUMVALUECOMPARATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>

#include "proto_nmea/format/ProtocolFormat.h"
#include "proto_nmea/Errors.h"
#include "proto_nmea/utility/HexUtils.h"
#include "proto_nmea/utility/StringUtils.h"

#ifdef UNIT_TEST

int compareChecksumData_testWrapper(const unsigned char *checksumString, unsigned int calculatedChecksum);

#endif

int compareChecksumData(const unsigned char *checksumString, unsigned int calculatedChecksum);

#ifdef __cplusplus
}
#endif
#endif //PROTO_NMEA_CHECKSUMVALUECOMPARATOR_H
