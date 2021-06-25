cmake_minimum_required(VERSION 3.19)
project(tinycim_cli VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

# add library: argparse
include_directories (src/argparse)
add_subdirectory (src/argparse)
set(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS} argparse)

# source set
set(SOURCES
        src/main.c)

# executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${THIRD_PARTY_LIBS} tinycim::lib)