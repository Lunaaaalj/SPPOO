cmake_minimum_required(VERSION 3.10)
project(MyProject)

enable_testing()

add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(my_executable main.cpp)
target_link_libraries(my_executable ${GTEST_LIBRARIES} pthread)