#!/bin/bash

# Source file containing test cases
SOURCE_FILE="./tests/Assert_test.cpp"
# Temporary file used during compilation
TEMP_FILE="./build/temp_assert_test.cpp"
# Name of the compiled executable
EXECUTABLE="./build/assert_test"

# Pattern used to identify test cases in the source file
TEST_PATTERN="// RUN_TEST"

# ANSI color codes
ERROR='\e[31m'   # RED
WARN='\e[33m'    # YELLOW
SUCCESS='\e[32m' # GREEN
INFO='\e[34m'    # BLUE
NOCOLOR='\e[0m'

#######################################
# Extracts test case names from the source file.
# Globals:
#   SOURCE_FILE
#   TEST_PATTERN
# Arguments:
#   None
# Outputs:
#   Populates TEST_CASES array with extracted test names.
#######################################
ExtractTests() {
    mapfile -t TEST_CASES < <(grep -oP "^\s*${TEST_PATTERN} \K.*" "${SOURCE_FILE}")
    if [[ ${#TEST_CASES[@]} -eq 0 ]]; then
        echo -e "${ERROR}No test cases found in ${SOURCE_FILE}${NOCOLOR}"
        exit 1
    fi
}

#######################################
# Compiles the source file with optional compiler flags.
# Globals:
#   EXECUTABLE
#   TEMP_FILE
# Arguments:
#   $1 - Compiler flag (e.g., -DNDEBUG)
# Returns:
#   0 if compilation succeeds, non-zero on failure.
#######################################
Compile() {
    local NDEBUG_FLAG="$1"
    clang++ @compile_flags.txt "${NDEBUG_FLAG}" -o "${EXECUTABLE}" "${TEMP_FILE}" || return 1
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
    local NDEBUG_FLAG="$1"
    local MODE=""
    MODE=$( [[ "$NDEBUG_FLAG" == "-DNDEBUG" ]] && echo "NoDebug" || echo "Debug" )
    for TEST_CASE in "${TEST_CASES[@]}"; do
        echo -e "${INFO}--------------------------------------${NOCOLOR}"
        echo -e "${INFO}Running mode: ${MODE} | Test case: '${TEST_CASE}'${NOCOLOR}"

        # Replace the test case identifier with actual test function call
        sed "s|${TEST_PATTERN} ${TEST_CASE}|${TEST_CASE}|g" "${SOURCE_FILE}" > "${TEMP_FILE}"
        Compile "${NDEBUG_FLAG}" && ./${EXECUTABLE}

        echo
    done
}

#######################################
# - Extract test cases from source file
# - Compile & Run tests in Debug
# - Compile & Run tests in NoDebug
#######################################
Main() {
    ExtractTests
    RunTests "-DNDEBUG"
    RunTests ""
}

Main
rm -f "${TEMP_FILE}"
echo -e "${SUCCESS}All tests completed.${NOCOLOR}"
