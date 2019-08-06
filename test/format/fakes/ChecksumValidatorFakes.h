//
// Created by timor on 04/08/2019.
//

#ifndef PROTO_NMEA_CHECKSUMVALIDATORFAKES_H
#define PROTO_NMEA_CHECKSUMVALIDATORFAKES_H

#include <fff.h>
#include <proto_nmea/format/ChecksumValidator.h>

#ifdef __cplusplus
extern "C"
{
#endif

DECLARE_FAKE_VALUE_FUNC(int8_t, validateChecksum, const unsigned char*, size_t)

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_CHECKSUMVALIDATORFAKES_H
