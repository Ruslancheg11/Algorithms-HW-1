cmake_minimum_required(VERSION 3.13)

if(TEST_SOURCE_FILES)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(${PROJECT_Test} ${TEST_SOURCE_FILES})
    target_link_libraries(${PROJECT_Test}
            ${PROJECT_Lib}
            GTest::gtest_main)

    if(BUILD_GMOCK)
        target_link_libraries(${PROJECT_Test} GTest::gmock_main)
    endif()


    # In order to get rid of "..." and "../../src" in #include directives
    target_include_directories(${PROJECT_Test} PRIVATE ${PROJECT_HDR_DIR})
    target_include_directories(${PROJECT_Test} PRIVATE ${PROJECT_SRC_DIR})

    add_test("${PROJECT_NAME}_GTests" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_Test}")
endif()