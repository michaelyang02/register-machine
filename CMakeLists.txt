cmake_minimum_required(VERSION 3.22)
project(register_machine C)

set(CMAKE_C_STANDARD 11)

add_executable(regmac main.c register_machine.c register_machine.h)
