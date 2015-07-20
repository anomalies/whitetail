cmake_minimum_required(VERSION 2.6)
project(whitetail)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c90 -Wall -Wextra -Werror -pedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(whitetail whitetail.c)

install(TARGETS whitetail RUNTIME DESTINATION bin)
