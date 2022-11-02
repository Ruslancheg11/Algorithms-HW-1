cmake_minimum_required(VERSION 3.13)

set(WINDOWS_INTERNAL_LIBRARIES_LIST
        ""
        )
#
set(UNIX_INTERNAL_LIBRARIES_LIST
        ""
        )
#
if(WIN32 AND WINDOWS_INTERNAL_LIBRARIES_LIST)
    message(STATUS "Linking for Windows platform:")
    foreach(LIBRARY IN LISTS WINDOWS_INTERNAL_LIBRARIES_LIST)
        message(STATUS "Linking ${LIBRARY}:")
        target_link_libraries(${PROJECT_Lib} PUBLIC ${LIBRARY})
    endforeach()
elseif(UNIX AND UNIX_INTERNAL_LIBRARIES_LIST)
    message(STATUS "Linking for Unix platform:")
    foreach(LIBRARY IN LISTS UNIX_INTERNAL_LIBRARIES_LIST)
        message(STATUS "Linking ${LIBRARY}:")
        target_link_libraries(${PROJECT_Lib} PUBLIC ${LIBRARY})
    endforeach()
endif()
#
set(EXTERNAL_HO_LIBRARIES_LIST
        ""
        )
#
if(EXTERNAL_HO_LIBRARIES_LIST)
    message(STATUS "External header-only library including")
    foreach(LIBRARY IN LISTS EXTERNAL_HO_LIBRARIES_LIST)
        message(STATUS "Including ${LIBRARY}")
        target_include_directories(${PROJECT_Lib} PUBLIC "${LIBRARY}/include/${LIBRARY}")
    endforeach()
else()
    message(STATUS "No header-only libraries to include")
endif()

set(GTEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/googletest")
set(GTEST_BENCHMARK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gtest-benchmark")


if(EXISTS "${GTEST_PATH}/CMakeLists.txt")
    set(GTEST_FOUND ON PARENT_SCOPE)
    message(STATUS "Found gtest")

    add_subdirectory(${GTEST_PATH} EXCLUDE_FROM_ALL)
else()
    set(GTEST_FOUND OFF PARENT_SCOPE)
    message(STATUS "gtest is not found")
endif()

if(EXISTS "${GTEST_BENCHMARK_PATH}/CMakeLists.txt")
    set(GTEST_BENCHMARK_FOUND ON PARENT_SCOPE)
    message(STATUS "Found gtest-benchmark")

    if (${GTEST_FOUND})
        set(GOOGLETEST_PATH ${GTEST_PATH})
    else()
        set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
    endif()

    if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
        # to get rid of the stupid warning "***WARNING*** Library was built as DEBUG. Timings may be affected"
        # from benchmark library which appears even if you compiled it all in release mode
        add_definitions(-DNDEBUG)
    endif()

    add_subdirectory(${GTEST_BENCHMARK_PATH} EXCLUDE_FROM_ALL)
else()
    set(GTEST_BENCHMARK_FOUND OFF PARENT_SCOPE)
    message(STATUS "gtest-benchmark is not found")
endif()