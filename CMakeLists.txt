cmake_minimum_required(VERSION 3.27)
project(GoLogicDLL)

set(CMAKE_CXX_STANDARD 11)

add_executable(GoLogicDLL main.cpp
        GoLogic.cpp
        GoLogic.h)
