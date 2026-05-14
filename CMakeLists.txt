cmake_minimum_required(VERSION 3.10)
project(app C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(include core)

set(SRC_DIR src)

file(GLOB SRCS "${SRC_DIR}/*.c")

add_executable(app ${SRCS})