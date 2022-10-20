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