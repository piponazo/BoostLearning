# Check if the conan file exist to find the dependencies
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    #conan_basic_setup()
    conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS SKIP_STD TARGETS)
endif()

set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_NO_SYSTEM_PATHS ON)
#set(Boost_DEBUG ON)
#set(Boost_REALPATH ON)

find_package(Boost 1.70 REQUIRED COMPONENTS system date_time thread)

