#!/bin/bash

# Source file containing test cases
SOURCE_FILE="./tests/Assert_test.cpp"
# Name of the compiled executable
EXECUTABLE="./build/assert_test"
EXECUTABLE_NDEBUG="./build/assert_test_NDEBUG"
# Exit code when tests finishes
EXIT_TESTS_FINISH=3


# ANSI color codes
ERROR='\e[31m'   # RED
WARN='\e[33m'    # YELLOW
SUCCESS='\e[32m' # GREEN
INFO='\e[34m'    # BLUE
NOCOLOR='\e[0m'

#######################################
# Compiles the source file with optional compiler flags.
# Globals:
#   EXECUTABLE
# Arguments:
#   $1 - Compiler flag (e.g., -DNDEBUG)
# Returns:
#   0 if compilation succeeds, non-zero on failure.
#######################################
Compile() {
    rm -rf ./build/
    mkdir -p build
    echo -e "${INFO}--------------------------------------${NOCOLOR}"
    echo -e "Building"
    clang++ @compile_flags.txt -o "${EXECUTABLE}" "${SOURCE_FILE}" || return 1
    clang++ @compile_flags.txt "-DNDEBUG" -o "${EXECUTABLE_NDEBUG}" "${SOURCE_FILE}" || return 1
}

#######################################
# Runs extracted test cases.
# Globals:
#   EXECUTABLE
#   SOURCE_FILE
#   TEMP_FILE
#   TEST_PATTERN
# Arguments:
#   $1 - Compiler flag (e.g., -DNDEBUG)
#######################################
RunTests() {
    local EXECUTABLE="$1"
    local MODE=""
    MODE=$( [[ "$EXECUTABLE" == "${EXECUTABLE_NDEBUG}" ]] && echo "Debug" || echo "NoDebug" )


    local i=0
    while true; do
        echo -e "${INFO}--------------------------------------${NOCOLOR}"
        echo -e "${INFO}Running mode: ${MODE} | Test index: ${i}${NOCOLOR}"
        "${EXECUTABLE}" --test "${i}"

        if [[ $? -eq "${EXIT_TESTS_FINISH}" ]]; then
            break
        fi
        ((i++))
    done

}

#######################################
# Compile and run the tests on each mode
#######################################
Compile
RunTests "${EXECUTABLE}"
RunTests "${EXECUTABLE_NDEBUG}"
