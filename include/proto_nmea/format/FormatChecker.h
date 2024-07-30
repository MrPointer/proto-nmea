//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_FORMATCHECKER
#define PROTO_NMEA_FORMATCHECKER

#include <inttypes.h>
#include <ctype.h>
#include <string.h>

#include "../utility/StringUtils.h"

#include "../Errors.h"
#include "ProtocolFormat.h"
#include "checksum/MessageChecksumValidator.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Validates the format of the given messages, which supposed to be an NMEA message.
 * Validation includes general format checks, checksum, etc.
 * @param message C-Style Null-Terminated string representing the message to validate.
 * @return Precise error code (negative number) representing the error cause, 0 if valid.
 */
int8_t validateMessageFormat(const char *message);

/**
 * Validates the format of the given messages, which supposed to be an NMEA message.
 * Validation includes general format checks, checksum, etc.
 * @param message C-Style Null-Terminated string representing the message to validate.
 * @param messageSize Size of the given message in bytes. Can be the result of strlen.
 * @return Precise error code (negative number) representing the error cause, 0 if valid.
 */
int8_t validateFixedSizeMessageFormat(const char *message, size_t messageSize);

#ifdef __cplusplus
}
#endif

#endif
