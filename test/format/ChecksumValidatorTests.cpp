//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include <string>

#include "../CatchSmartInclude.hpp"
#include "../utility/fakes/FakeUtils.h"

#include <proto_nmea/format/ChecksumValidator.h>
#include "fakes/ChecksumValidatorFakes.h"

SCENARIO("ChecksumValidator handles invalid arguments")
{
    DISABLE_FAKE(validateChecksum)

    GIVEN("Null string")
    {
        std::string nullMessage{'\0'};

        WHEN("Checksum is validated")
        {
            auto result = validateChecksum(reinterpret_cast<const unsigned char *>(nullMessage.c_str()), 0);

            THEN("Null string error is returned")
            {
                REQUIRE(result == -ENULL_STRING);
            }
        }
    }
}
