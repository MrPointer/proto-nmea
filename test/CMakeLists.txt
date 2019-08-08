cmake_minimum_required(VERSION 3.8.2)

set(C_STANDARD 11)
set(CXX_STANDARD 14)

add_executable(proto-nmea-tests test_main.cpp
        format/FormatCheckerTests.cpp format/MessageChecksumValidatorTests.cpp
        format/fakes/ChecksumValidatorFakes.c format/fakes/ChecksumFormatValidatorFakes.c
        format/fakes/ChecksumValueComparatorFakes.c
        utility/TypeConversionUtils.cpp)

target_include_directories(proto-nmea-tests PRIVATE dependencies ../include)
target_link_libraries(proto-nmea-tests PRIVATE proto-nmea-lib)

# Use Catch as the testing framework
find_package(Catch2)

if (NOT Catch2_FOUND)
    message(AUTHOR_WARNING "Couldn't find Catch2 in the system, resorting to a single-header version")
else () # Use library from the package and bind it to CTest
    target_link_libraries(proto-nmea-tests PRIVATE Catch2::Catch2)
    target_compile_definitions(proto-nmea-tests PRIVATE CATCH_SYSTEM_PACKAGE)
    include(CTest)
    include(Catch)
    catch_discover_tests(proto-nmea-tests)
endif ()
