//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_STRINGUTILS_H
#define PROTO_NMEA_STRINGUTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

#define NULL_CHAR '\0'

#define IS_NULL_STRING(str) (str == NULL || *str == NULL_CHAR)

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_STRINGUTILS_H
