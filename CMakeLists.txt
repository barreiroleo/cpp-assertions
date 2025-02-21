cmake_minimum_required(VERSION 3.28)
project(cpp-assertions)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakeDependentOption)
option(ASSERTION_TESTS "Run the assertion tests script." OFF)

add_subdirectory(src)

# Run tests requires build option: `cmake -B build -DASSERTION_TESTS=ON`
if(ASSERTION_TESTS)
    add_subdirectory(tests)
endif()
