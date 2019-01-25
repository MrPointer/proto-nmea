cmake_minimum_required(VERSION 3.8.2)

project(proto-nmea-tests LANGUAGES C CXX)

set(C_STANDARD 11)
set(CXX_STANDARD 14)

add_executable(proto-nmea-tests test_main.cpp
        format/FormatCheckerTests.cpp)

target_include_directories(proto-nmea-tests PRIVATE dependencies ../include)
target_link_libraries(proto-nmea-tests PRIVATE proto-nmea-lib)
