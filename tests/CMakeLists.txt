# Run tests requires build option: `cmake -B build -DASSERTION_TESTS=ON`

message(DEBUG "Building assertion tests: ${PROJECT_SOURCE_DIR}/run_tests.sh")
if(NOT UNIX)
    message(WARNING "Tests can only be run on Linux at the moment. PRs are welcome.")
    return()
endif()

set(TESTS_DEBUG_BINARY ${PROJECT_NAME}-tests-debug)
set(TESTS_NDEBUG_BINARY ${PROJECT_NAME}-tests-ndebug)

add_executable(${TESTS_DEBUG_BINARY} Assert_test.cpp)
target_link_libraries(${TESTS_DEBUG_BINARY} PRIVATE ${PROJECT_NAME})

add_executable(${TESTS_NDEBUG_BINARY} Assert_test.cpp)
target_link_libraries(${TESTS_NDEBUG_BINARY} PRIVATE ${PROJECT_NAME})
target_compile_definitions(${TESTS_NDEBUG_BINARY} PRIVATE NDEBUG)

add_custom_target(run_tests
        COMMENT "Running tests"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND chmod +x ./run_tests.sh
        COMMAND ./run_tests.sh
                ${PROJECT_BINARY_DIR}/tests/${TESTS_DEBUG_BINARY}
                ${PROJECT_BINARY_DIR}/tests/${TESTS_NDEBUG_BINARY}
)
