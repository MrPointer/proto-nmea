cmake_minimum_required(VERSION 3.8.2)

project(proto-nmea-tests LANGUAGES CXX)

add_executable(proto-nmea-tests test_main.cpp
        format-checker/format-check-tests.cpp)

target_include_directories(proto-nmea-tests PRIVATE dependencies ../include)
target_link_libraries(proto-nmea-tests PRIVATE proto-nmea-lib)
