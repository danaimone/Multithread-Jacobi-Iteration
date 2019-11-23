cmake_minimum_required(VERSION 3.10)
project(jacobi C)

set(CMAKE_C_STANDARD 99)

add_executable(jacobi main.c barrier.c barrier.h main.h cthread.c cthread.h)