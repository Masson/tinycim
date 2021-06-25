cmake_minimum_required(VERSION 3.19)
project(libtinycim VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

# add library: libuv
add_subdirectory (src/libuv)
set(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS} uv_a)

# source set
set(SOURCES
        src/imclient.c)

# library
add_library(${PROJECT_NAME} ${SOURCES})
add_library(tinycim::lib ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${THIRD_PARTY_LIBS})