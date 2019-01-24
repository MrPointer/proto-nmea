cmake_minimum_required(VERSION 3.8.2)

project(proto-nmea-lib LANGUAGES C)

add_library(proto-nmea-lib STATIC format_checker/FormatChecker.c messageParser.c ../include/proto_nmea/messageParser.h)

target_include_directories(proto-nmea-lib PUBLIC ../include)
