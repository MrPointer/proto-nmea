//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_MOCKUTILS_H
#define PROTO_NMEA_MOCKUTILS_H

#include <fff.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Enables a FFF fake for the given function, expecting that a matching fake has already been defined before
 */
#define ENABLE_FFF_FAKE(faked_function) RESET_FAKE(faked_function)

/**
 * Disables a FFF fake for the given function by resetting it and
 * setting its' custom callback to the function's test wrapper. <br>
 * It expects that a matching fake has already been defined.
 */
#define DISABLE_FAKE(faked_function) \
    RESET_FAKE(faked_function) \
    faked_function##_fake.custom_fake = faked_function##_testWrapper;

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_MOCKUTILS_H
