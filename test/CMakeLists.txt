cmake_minimum_required(VERSION 3.8.2)

project(proto-nmea-tests LANGUAGES CXX)

add_executable(proto-nmea-tests main.cpp)

target_include_directories(proto-nmea-tests PRIVATE dependencies ../include)
