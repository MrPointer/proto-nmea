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
        return -EMISSING_CHECKSUM;

    // Iterate over all data elements to validate they're representing hex values.
    // Start from delimiter's length to skip it.
    for (int i = CHECKSUM_DELIMITER_LENGTH; i <= CHECKSUM_DATA_LENGTH; ++i)
    {
        if (!isHex(checksumString[i]))
            return -EUNEXPECTED_CHECKSUM_FORMAT;
    }

    return EVALID;
}

#ifdef UNIT_TEST

int8_t validateChecksumFormat_testWrapper(const unsigned char *checksumString)
{
    return validateChecksumFormat(checksumString);
}

#endif
