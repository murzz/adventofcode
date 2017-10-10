cmake_minimum_required(VERSION 2.8)

project(adventofcode)

include(${CMAKE_CURRENT_LIST_DIR}/mk/CompilerFlags.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mk/Boost.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mk/add_test.cmake)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
