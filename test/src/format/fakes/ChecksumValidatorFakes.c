//
// Created by timor on 04/08/2019.
//

#include "proto_nmea_test/fakes/format/ChecksumValidatorFakes.h"

DEFINE_FAKE_VALUE_FUNC(int8_t, validateMessageChecksum, const unsigned char*, size_t)
