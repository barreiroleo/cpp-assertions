message(DEBUG "Including header-only library: ${PROJECT_NAME}")
add_library(${PROJECT_NAME} INTERFACE ./Assert.hpp)
target_include_directories(${PROJECT_NAME} INTERFACE .)
