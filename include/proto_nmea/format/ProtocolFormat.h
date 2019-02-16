//
// Copyright (c) 2019 Takpit. All rights reserved.
//

#ifndef PROTO_NMEA_PROTOCOLFORMAT_H
#define PROTO_NMEA_PROTOCOLFORMAT_H

#ifdef __cplusplus
extern "C"
{
#endif

//region Special Values

#define PROTOCOL_START_CHAR '$'
#define PROTOCOL_STOP_CHAR_1 '\r'
#define PROTOCOL_STOP_CHAR_2 '\n'
#define PROTOCOL_FIELD_DELIMITER ','
#define PROTOCOL_CHECKSUM_DELIMITER '*'

#define TALKER_PROPRIETARY_ID 'P'
#define TALKER_GNSS_ID 'G'

//endregion

//region Lengths

#define PROTOCOL_START_LENGTH 1
#define PROTOCOL_STOP_LENGTH 2

#define PROTOCOL_DELIMITER_LENGTH 1

#define CHECKSUM_DELIMITER_LENGTH 1
#define CHECKSUM_DATA_LENGTH 2
#define CHECKSUM_FULL_LENGTH (CHECKSUM_DATA_LENGTH + CHECKSUM_DELIMITER_LENGTH)

#define TALKER_ID_MIN_LENGTH 1
#define TALKER_ID_MAX_LENGTH 2

#define MESSAGE_ID_LENGTH 3

#define MESSAGE_TYPE_MIN_LENGTH (TALKER_ID_MIN_LENGTH + MESSAGE_ID_LENGTH)
#define MESSAGE_TYPE_MAX_LENGTH (TALKER_ID_MAX_LENGTH + MESSAGE_ID_LENGTH)

// The general form is "$PGGA,*12\r\n"
#define MESSAGE_MIN_LENGTH (PROTOCOL_START_LENGTH + MESSAGE_TYPE_MIN_LENGTH + 1 + \
                            CHECKSUM_FULL_LENGTH + PROTOCOL_STOP_LENGTH )
#define MESSAGE_MAX_LENGTH 90

//endregion

//region Indices

#define MESSAGE_TYPE_START_INDEX PROTOCOL_START_LENGTH

#define MESSAGE_DATA_START_MIN_INDEX (MESSAGE_TYPE_START_INDEX + TALKER_ID_MIN_LENGTH + MESSAGE_ID_LENGTH)
#define MESSAGE_DATA_START_MAX_INDEX (MESSAGE_TYPE_START_INDEX + TALKER_ID_MAX_LENGTH + MESSAGE_ID_LENGTH)

//endregion

#ifdef __cplusplus
}
#endif

#endif //PROTO_NMEA_PROTOCOLFORMAT_H
