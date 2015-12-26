enable_testing()
include_directories(${Boost_INCLUDE_DIRS})

macro(adventofcode_add_test DAY_NAME)

    add_executable(${DAY_NAME} test.cpp)
    target_link_libraries(${DAY_NAME} ${Boost_LIBRARIES})
    
    add_test(${DAY_NAME} ${DAY_NAME})

endmacro()