cmake_minimum_required(VERSION 3.10)
project(MyProject)


# Find all source files recursively
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Group source files
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${SOURCES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create the executable
add_executable(my_program ${SOURCES})

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
# Set compiler optimization flags for Release builds
if(CMAKE_BUILD_TYPE_LOWER STREQUAL "release")
    target_compile_options(my_program PRIVATE -O3 -DNDEBUG) # -DNDEBUG disables debug asserts
elseif(CMAKE_BUILD_TYPE_LOWER STREQUAL "debug")
    target_compile_options(my_program PRIVATE -g) # Debug flags
endif()

target_compile_features(my_program PRIVATE cxx_std_20)
target_compile_options(my_program PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra>
    $<$<CONFIG:Release>:-Wall -Wextra>
)
#Set output directory
set_target_properties(my_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
)