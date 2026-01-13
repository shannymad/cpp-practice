cmake_minimum_required(VERSION 3.14)
project(TaskC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(taskc solution.cpp)
target_include_directories(taskc PRIVATE include)