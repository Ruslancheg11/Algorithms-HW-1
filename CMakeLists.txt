cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME Matrix)

project(${PROJECT_NAME}
        VERSION 1.0
        DESCRIPTION ""
        LANGUAGES CXX C)

enable_testing()


# configure options
option("${PROJECT_NAME}_FORCE_BUILD" "Use for running on not configured platform" OFF)
option("${PROJECT_NAME}_BUILD_INTERFACE" "Use for build it like interface library" OFF)
option("${PROJECT_NAME}_BUILD_SHARED" "Use for build it like SHARED library" OFF)


if(${${PROJECT_NAME}_BUILD_INTERFACE})
    set(PROJECT_BUILD_TYPE "INTERFACE")
elseif(${${PROJECT_NAME}_BUILD_SHARED})
    set(PROJECT_BUILD_TYPE "SHARED")
else()
    set(PROJECT_BUILD_TYPE "STATIC")
endif()

message(STATUS "Building: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "OS: ${CMAKE_SYSTEM_NAME} v${CMAKE_SYSTEM_VERSION}")
message(STATUS "CPU: ${CMAKE_SYSTEM_PROCESSOR}")

if(NOT WIN32 AND NOT UNIX)
    if(NOT ${${PROJECT_NAME}_FORCE_BUILD})
        message(FATAL_ERROR "Build preferences is not configured for your platform. If you still want to build it use -D${PROJECT_NAME}_FORCE_BUILD=ON")
    else()
        message(WARNING "Building under ${PROJECT_NAME}FORCE_BUILD")
    endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(PROJECT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROJECT_HDR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}")
set(TEST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/testing/unit")
set(BENCHMARK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/testing/benchmark")


# For editing
set(APPLICATION_ENTRYPOINT
        main.cpp
        ) # main.cpp file
#
set(PROJECT_SOURCE_FILES_LIST
        matrix.cpp
        base_matrix.cpp
        generator.cpp
        search.cpp
        ) # Project's cpp files
#
#
#
set(PROJECT_HEADER_FILES_LIST
        matrix.hpp
        base_matrix.hpp
        generator.hpp
        search.hpp
        ) # Project's hpp files
#
#
#
set(TEST_SOURCE_FILES_LIST
        test_main.cpp
        test_utility.cpp
        generator_test.cpp
        search_test.cpp
        ) # Test's cpp files
#
#
#
set(BENCHMARK_SOURCE_FILES_LIST
        benchmark_main.cpp
        generator_benchmark.cpp
        search_benchmark.cpp
        ) # Benchmark's cpp files


# shortcuts
set(PROJECT_Lib "${PROJECT_NAME}_Lib")
set(PROJECT_App "${PROJECT_NAME}_App")
set(PROJECT_Test "${PROJECT_NAME}_Test")
set(PROJECT_Benchmark "${PROJECT_NAME}_Benchmark")
#
set(PROJECT_SOURCE_FILES)
set(PROJECT_HEADER_FILES)
set(TEST_SOURCE_FILES)
set(BENCHMARK_SOURCE_FILES)
#


#
set(APPLICATION_ENTRYPOINT_FILE "${PROJECT_SRC_DIR}/${APPLICATION_ENTRYPOINT}")
#
foreach(FILE IN LISTS PROJECT_SOURCE_FILES_LIST)
    list(APPEND PROJECT_SOURCE_FILES "${PROJECT_SRC_DIR}/${FILE}")
endforeach()
#
foreach(FILE IN LISTS PROJECT_HEADER_FILES_LIST)
    list(APPEND PROJECT_HEADER_FILES "${PROJECT_HDR_DIR}/${FILE}")
endforeach()
#
foreach(FILE IN LISTS TEST_SOURCE_FILES_LIST)
    list(APPEND TEST_SOURCE_FILES "${TEST_SRC_DIR}/${FILE}")
endforeach()
#
foreach(FILE IN LISTS BENCHMARK_SOURCE_FILES_LIST)
    list(APPEND BENCHMARK_SOURCE_FILES "${BENCHMARK_SRC_DIR}/${FILE}")
endforeach()
#


# Creating library of the project, in order to have opportunity to link it with anything we want to
message(STATUS "Building ${PROJECT_NAME} as ${PROJECT_BUILD_TYPE} library")
add_library(${PROJECT_Lib} ${PROJECT_BUILD_TYPE} ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})

set_property(
        TARGET ${PROJECT_Lib}
        PROPERTY CXX_STANDARD 11
        PROPERTY CXX_STANDARD_REQUIRED ON
        PROPERTY CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-2"
        PROPERTY CMAKE_CXX_FLAGS_RELEASE "-O3"
)


# In order to get rid of the quotes and "../../src" in #include directives
if("${PROJECT_BUILD_TYPE}" STREQUAL "INTERFACE")
    target_include_directories(${PROJECT_Lib} INTERFACE ${PROJECT_HDR_DIR})
    target_include_directories(${PROJECT_Lib} INTERFACE ${PROJECT_SRC_DIR})
else()
    target_include_directories(${PROJECT_Lib} PRIVATE ${PROJECT_HDR_DIR})
    target_include_directories(${PROJECT_Lib} PRIVATE ${PROJECT_SRC_DIR})
endif()
#

add_subdirectory(external)
add_subdirectory(testing)

if(APPLICATION_ENTRYPOINT_FILE)

    # if we have a main.cpp file, which is entrypoint for out library
    add_executable(${PROJECT_App} ${APPLICATION_ENTRYPOINT_FILE})

    if(NOT ${PROJECT_BUILD_TYPE} STREQUAL "INTERFACE")

        # if it is a library, which needs to be linked
        target_link_libraries(${PROJECT_App} PRIVATE ${PROJECT_Lib})

    endif()

    # otherwise, if it is just a header-only library, which doesn't need to be linked
    target_include_directories(${PROJECT_App} PRIVATE ${PROJECT_HDR_DIR})

endif()
