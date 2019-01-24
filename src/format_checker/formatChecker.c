#include "proto_nmea/format_checker/formatChecker.h"

int8_t validateMessageFormat(const char *rawMessage)
{
    if (rawMessage[0] != '$')
        return -EINVAL_NMEA_MESSAGE_START;
    return 0;
}
