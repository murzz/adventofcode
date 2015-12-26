cmake_minimum_required(VERSION 2.8)

project(adventofcode)

include(mk/CompilerFlags.cmake)
include(mk/Boost.cmake)

enable_testing()
add_subdirectory(day1)
