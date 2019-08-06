cmake_minimum_required(VERSION 3.8.2)

add_library(proto-nmea-lib STATIC
        format/FormatChecker.c format/checksum/MessageChecksumValidator.c
        utility/ChecksumUtils.c utility/HexUtils.c)

target_include_directories(proto-nmea-lib PUBLIC ../include)

if (UNIT_TEST)
    target_compile_definitions(proto-nmea-lib PUBLIC UNIT_TEST)
endif ()

# Explictly define the compiler ID for the target - Mostly needed to aid CLion's insights
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    target_compile_definitions(proto-nmea-lib PRIVATE "__GNUC__")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_definitions(proto-nmea-lib PRIVATE "__MSVC__")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    target_compile_definitions(proto-nmea-lib PRIVATE "__CLANG__")
endif ()
