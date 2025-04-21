cmake_minimum_required(VERSION 3.30)
project(WWPuzzleReplicate)

set(CMAKE_CXX_STANDARD 20)

add_executable(WWPuzzleReplicate main.cpp
        Cards.cpp
        Cards.h
        GameLogic.cpp
        GameLogic.h)
