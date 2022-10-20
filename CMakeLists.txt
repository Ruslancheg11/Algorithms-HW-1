cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-2")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "")

set(PROJECT_NAME Matrix)

project(${PROJECT_NAME}
        VERSION 1.0
        DESCRIPTION ""
        LANGUAGES CXX C)
enable_testing()


# configure options
option(FORCE_BUILD "Use for running on not configured platform" OFF)
option(BUILD_INTERFACE "Use for build it like interface library" OFF)
option(BUILD_SHARED "Use for build it like SHARED library" OFF)
set(BUILD_GMOCK OFF)


if(BUILD_INTERFACE)
    set(PROJECT_BUILD_TYPE "INTERFACE")
elseif(BUILD_SHARED)
    set(PROJECT_BUILD_TYPE "SHARED")
else()
    set(PROJECT_BUILD_TYPE "STATIC")
endif()



message(STATUS "Building: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "OS: ${CMAKE_SYSTEM_NAME} v${CMAKE_SYSTEM_VERSION}")
message(STATUS "CPU: ${CMAKE_SYSTEM_PROCESSOR}")

if(NOT WIN32 AND NOT UNIX)
    if(NOT FORCE_BUILD)
        message(FATAL_ERROR "Build preferences is not configured for your platform. If you still want to build it use -DFORCE_BUILD=ON")
    else()
        message(WARNING "Building under FORCE_BUILD")
    endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(PROJECT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROJECT_HDR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}")
set(TEST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")


# For editing
set(APPLICATION_ENTRYPOINT
        main.cpp
        ) # main.cpp file
#
set(PROJECT_SOURCE_FILES_LIST
        generator.cpp
        finder.cpp
        ) # Project's cpp files
#
set(PROJECT_HEADER_FILES_LIST
        generator.hpp
        finder.hpp
        ) # Project's hpp files
#
set(TEST_SOURCE_FILES_LIST
        test.cpp
        generator_test.cpp
        finder_test.cpp
        ) # Test's cpp files


# shortcuts
set(PROJECT_Lib "${PROJECT_NAME}_Lib")
set(PROJECT_App "${PROJECT_NAME}_App")
set(PROJECT_Test "${PROJECT_NAME}_Test")
#
set(PROJECT_SOURCE_FILES)
set(PROJECT_HEADER_FILES)
set(TEST_SOURCE_FILES)
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


# Creating library of the project, in order to link it with gtest
message(STATUS "Building ${PROJECT_NAME} as ${PROJECT_BUILD_TYPE} library")
add_library(${PROJECT_Lib} ${PROJECT_BUILD_TYPE} ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})


# In order to get rid of "..." and "../../src" in #include directives
if("${PROJECT_BUILD_TYPE}" STREQUAL "INTERFACE")
    target_include_directories(${PROJECT_Lib} INTERFACE ${PROJECT_HDR_DIR})
    target_include_directories(${PROJECT_Lib} INTERFACE ${PROJECT_SRC_DIR})
else()
    target_include_directories(${PROJECT_Lib} PRIVATE ${PROJECT_HDR_DIR})
    target_include_directories(${PROJECT_Lib} PRIVATE ${PROJECT_SRC_DIR})
endif()
#

add_subdirectory(libs)
add_subdirectory(test)

if(APPLICATION_ENTRYPOINT_FILE)

    # if we have main.cpp file, which is entrypoint for out library
    add_executable(${PROJECT_App} ${APPLICATION_ENTRYPOINT_FILE})

    if(NOT ${PROJECT_BUILD_TYPE} STREQUAL "INTERFACE")

        # if it is a library, which needs to be linked
        target_link_libraries(${PROJECT_App} PRIVATE ${PROJECT_Lib})

    endif()

    # otherwise, if it is just a header-only library, which doesn't need to be linked
    target_include_directories(${PROJECT_App} PRIVATE ${PROJECT_HDR_DIR})

endif()
