cmake_minimum_required(VERSION 2.8)

project(day1)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

add_test(${PROJECT_NAME} ${PROJECT_NAME})