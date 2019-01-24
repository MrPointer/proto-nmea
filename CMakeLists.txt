cmake_minimum_required(VERSION 3.8.2)

project(proto-nmea LANGUAGES C CXX)

add_subdirectory(src)

if(TEST)
   add_subdirectory(test) 
endif()

