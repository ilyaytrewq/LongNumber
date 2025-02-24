cmake_minimum_required(VERSION 3.19)
project(LongMath)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

include_directories(LongNumber)
add_subdirectory(LongNumber)

target_link_libraries(main LongNumber)

add_executable(pi Pi_Calc.cpp)
target_link_libraries(pi)
target_link_libraries(pi LongNumber)

add_executable(test Tests.cpp)
target_link_libraries(test LongNumber)