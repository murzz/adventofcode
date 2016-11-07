enable_testing()
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

macro(adventofcode_add_test DAY_NAME)

    add_executable(${DAY_NAME} test.cpp)
    target_link_libraries(${DAY_NAME} ${Boost_LIBRARIES})
    
    add_test(NAME ${DAY_NAME}
        COMMAND ${DAY_NAME} --log_level=message
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

endmacro()