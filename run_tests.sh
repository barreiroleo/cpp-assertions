#!/bin/bash

#######################################
# Execution.
#   ./run_tests.sh [debug-binary] [ndebug-binary]
#   ./run_tests.sh ./build/tests/cpp-assertions-tests-ndebug ./build/tests/assertions-tests-ndebug
# Arguments:
#   $1 - Debug binary path
#   $2 - NDebug binary path
#######################################
EXECUTABLE="$1"
EXECUTABLE_NDEBUG="$2"

# Exit code when tests finishes
EXIT_TESTS_FINISH=3

# ANSI color codes
ERROR='\e[31m'   # RED
WARN='\e[33m'    # YELLOW
SUCCESS='\e[32m' # GREEN
INFO='\e[34m'    # BLUE
NOCOLOR='\e[0m'

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
    MODE=$( [[ "$EXECUTABLE" == "${EXECUTABLE_NDEBUG}" ]] && echo "NoDebug" || echo "Debug" )

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

RunTests "${EXECUTABLE_NDEBUG}"
RunTests "${EXECUTABLE}"
