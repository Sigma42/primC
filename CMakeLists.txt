cmake_minimum_required(VERSION 3.12)
project(primC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-march=native -Ofast -pthread")

add_executable(primC main.c)
add_executable(primRead read.c)

TARGET_LINK_LIBRARIES(primC pthread m)
