cmake_minimum_required(VERSION 3.27)
project(GoLogicDLL)

set(CMAKE_CXX_STANDARD 11)

add_executable(GoLogicDLL main.cpp
        src/headers/go_logic.h
        src/sources/go_logic.cpp
        src/sources/set_stone_logic.cpp)
