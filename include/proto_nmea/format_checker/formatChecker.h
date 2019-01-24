#ifndef PROTO_NMEA_FORMATCHECKER
#define PROTO_NMEA_FORMATCHECKER

#include <inttypes.h>

#include "../errors.h"

#ifdef __cplusplus
extern "C"
{
#endif

int8_t validateMessageFormat(const char *rawMessage);

#ifdef __cplusplus
}
#endif

#endif
