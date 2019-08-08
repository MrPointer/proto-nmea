//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "proto_nmea/format/checksum/ChecksumFormatValidator.h"

#ifdef UNIT_TEST

static
#endif
int8_t validateChecksumFormat(const unsigned char *checksumString)
{
    // Should start with a checksum delimiter
    if (checksumString[0] != PROTOCOL_CHECKSUM_DELIMITER)
    {
        if (strchr(((const char *) checksumString), PROTOCOL_CHECKSUM_DELIMITER))
            return -EMISSING_CHECKSUM_DATA;
        else
            return -EMISSING_CHECKSUM;
    }

    // ToDo: Iterate with for loop
    if (!isHex(checksumString[1]) || !isHex(checksumString[2]))
        return -EINVALID_CHECKSUM;

    return EVALID;
}

#ifdef UNIT_TEST

int8_t validateChecksumFormat_testWrapper(const unsigned char *checksumString)
{
    return validateChecksumFormat(checksumString);
}

#endif
