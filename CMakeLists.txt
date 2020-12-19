cmake_minimum_required(VERSION 3.10)
project(day9 LANGUAGES CXX)

add_executable(day9
    src/XmasProtocol.cpp
    src/main.cpp
)

set_property(TARGET day9 PROPERTY CXX_STANDARD 17)
