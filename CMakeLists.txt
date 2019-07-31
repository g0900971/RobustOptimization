cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(ro LANGUAGES C CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_VERBOSE_MAKEFILE FALSE)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG -march=native")
endif ()

set(default_build_type "DEBUG")
if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "DEBUG")
endif ()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "DEBUG" "RELEASE")
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(Boost REQUIRED)
find_package(cplex REQUIRED)
find_package(dl REQUIRED)
find_package(Threads REQUIRED)

set(HEADER_DEP ${Boost_INCLUDE_DIR} ${CPLEX_INCLUDE_DIR} ${CONCERT_INCLUDE_DIR})
set(LIBRARY_DEP ${Boost_LIBRARIES} ${CONCERT_LIBRARY} ${CPLEX_LIBRARY} ${LIBDL_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/src")
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(ro STATIC ${SOURCES})
target_include_directories(ro PUBLIC ${HEADERS} ${HEADER_DEP})
target_compile_definitions(ro PUBLIC -DIL_STD -D_USE_CPLEX_)

add_executable(ro-test1 ${CMAKE_SOURCE_DIR}/ExampleSourceCode/test_1.cpp)
target_link_libraries(ro-test1 ro ${LIBRARY_DEP})

add_executable(ro-test10 ${CMAKE_SOURCE_DIR}/ExampleSourceCode/test_10.cpp)
target_link_libraries(ro-test10 ro ${LIBRARY_DEP})

add_executable(ro-test13 ${CMAKE_SOURCE_DIR}/ExampleSourceCode/test_13.cpp)
target_link_libraries(ro-test13 ro ${LIBRARY_DEP})
