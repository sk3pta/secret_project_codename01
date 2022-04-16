cmake_minimum_required(VERSION 3.4) 
project(lab03_3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(solver STATIC ${CMAKE_CURRENT_SOURCE_DIR}/equation.cpp)
add_library(solver_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR} "../solver_lib/solver.cpp")
add_library(formatter_ex STATIC ${CMAKE_CURRENT_SOURCE_DIR} "../formatter_ex_lib/formatter_ex.cpp")

add_library(solver_application ${CMAKE_CURRENT_SOURCE_DIR}/equation.cpp)

include_directories("../formatter_ex_lib")
include_directories("../formatter_lib")
include_directories("../solver_lib")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stdexcept)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmath)

target_link_libraries(solver formatter_ex)
target_link_libraries(formatter_ex formatter_lib)
target_link_libraries(solver "../solver_lib")
target_link_libraries(solver_application solver_lib)
