cmake_minimum_required(VERSION 3.4) 
project(hello_world_application)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hello_world_application ${CMAKE_CURRENT_SOURCE_DIR}/hello_world.cpp)

include_directories("../formatter_ex_lib")

