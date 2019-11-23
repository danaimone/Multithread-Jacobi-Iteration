cmake_minimum_required(VERSION 3.10)
project(jacobi C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

include_directories(.)

add_executable(jacobi barrier.c barrier.h cthread.h main.h main.c)
