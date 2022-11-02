cmake_minimum_required(VERSION 3.13)

if(TEST_SOURCE_FILES AND ${GTEST_FOUND})

    add_executable(${PROJECT_Test} ${TEST_SOURCE_FILES})
    target_link_libraries(${PROJECT_Test}
            ${PROJECT_Lib}
            GTest::gtest_main)

    if(BUILD_GMOCK)
        target_link_libraries(${PROJECT_Test}
                GTest::gmock_main)
    endif()

    # In order to get rid of the quotes and "../../src" in #include directives
    target_include_directories(${PROJECT_Test} PRIVATE ${PROJECT_HDR_DIR})
    target_include_directories(${PROJECT_Test} PRIVATE ${PROJECT_SRC_DIR})
    target_include_directories(${PROJECT_Test} PRIVATE ${TEST_SRC_DIR})

    add_test("${PROJECT_NAME}_GTests" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_Test}")
endif()

if(BENCHMARK_SOURCE_FILES AND ${GTEST_BENCHMARK_FOUND})

    add_executable(${PROJECT_Benchmark} ${BENCHMARK_SOURCE_FILES})
    target_link_libraries(${PROJECT_Benchmark}
            ${PROJECT_Lib}
            benchmark::benchmark_main)

    # In order to get rid of the quotes and "../../src" in #include directives
    target_include_directories(${PROJECT_Benchmark} PRIVATE ${PROJECT_HDR_DIR})
    target_include_directories(${PROJECT_Benchmark} PRIVATE ${PROJECT_SRC_DIR})
endif()