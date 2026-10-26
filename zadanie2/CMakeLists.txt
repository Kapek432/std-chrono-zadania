cmake_minimum_required(VERSION 3.16)
project(CzasZadanie2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(program main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(program PRIVATE Threads::Threads)
