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


if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    # to get rid of the stupid warning "***WARNING*** Library was built as DEBUG. Timings may be affected"
    # from benchmark library which appears even if you compiled it all in release mode
    add_definitions(-DNDEBUG)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest EXCLUDE_FROM_ALL)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/benchmark EXCLUDE_FROM_ALL)

# user library linkling
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.80.0)
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_Lib} ${Boost_LIBRARIES})
#endif()