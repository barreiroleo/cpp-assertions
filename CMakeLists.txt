cmake_minimum_required(VERSION 3.28)
project(cpp-assertions)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakeDependentOption)
option(ASSERTION_TESTS "Run the assertion tests script." OFF)

add_library(${PROJECT_NAME} INTERFACE)
include_directories(${PROJECT_NAME} INTERFACE ./src/)

# Run tests requires build option: `cmake -B build -DASSERTION_TESTS=ON`
if(ASSERTION_TESTS)
    if(UNIX AND NOT APPLE)
        message(WARNING "Building assertion tests: ${PROJECT_SOURCE_DIR}/run_tests.sh")

        add_executable(${PROJECT_NAME}-tests-debug ./tests/Assert_test.cpp)

        add_executable(${PROJECT_NAME}-tests-ndebug ./tests/Assert_test.cpp)
        target_compile_definitions(${PROJECT_NAME}-tests-ndebug PRIVATE NDEBUG)

        add_custom_target(run_tests
            COMMENT "Running tests"
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMAND chmod +x ./run_tests.sh
            COMMAND ./run_tests.sh
        )
    else()
        message(WARNING "Tests can only be run on Linux at the moment. PRs are welcome.")
    endif()
endif()
