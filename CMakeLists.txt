cmake_minimum_required(VERSION 3.2)

project(adventofcode CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/externals/sanitizers-cmake/cmake")

include("${CMAKE_CURRENT_LIST_DIR}/mk/CompilerFlags.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/mk/test.cmake")

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
