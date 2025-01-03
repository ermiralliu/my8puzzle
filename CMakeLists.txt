cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Find all source files recursively
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(my_program ${SOURCES})

#Optional compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++20")

#Set output directory
set_target_properties(my_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)