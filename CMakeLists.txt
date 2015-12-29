cmake_minimum_required(VERSION 2.8)

project(adventofcode)

include(mk/CompilerFlags.cmake)
include(mk/Boost.cmake)
include(mk/add_test.cmake)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
