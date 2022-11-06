cmake_minimum_required(VERSION 3.13)

set(GTEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/googletest")
set(GTEST_BENCHMARK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gtest-benchmark")


if(EXISTS "${GTEST_PATH}/CMakeLists.txt")
    set(GTEST_FOUND ON PARENT_SCOPE)
    message(STATUS "Found gtest")

    add_subdirectory(${GTEST_PATH})
else()
    set(GTEST_FOUND OFF PARENT_SCOPE)
    message(STATUS "gtest is not found")
endif()

if(EXISTS "${GTEST_BENCHMARK_PATH}/CMakeLists.txt")
    set(GTEST_BENCHMARK_FOUND ON PARENT_SCOPE)
    message(STATUS "Found gtest-benchmark")

    if(${GTEST_FOUND})
        set(GOOGLETEST_PATH ${GTEST_PATH})
    else()
        set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
    endif()

    # to remove benchmark tests from CTest test list
    set(BENCHMARK_ENABLE_TESTING OFF)

    if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
        # to get rid of the stupid warning "***WARNING*** Library was built as DEBUG. Timings may be affected"
        # from benchmark library which appears even if you compiled it all in release mode
        add_definitions(-DNDEBUG)
    endif()

    add_subdirectory(${GTEST_BENCHMARK_PATH})
else()
    set(GTEST_BENCHMARK_FOUND OFF PARENT_SCOPE)
    message(STATUS "gtest-benchmark is not found")
endif()