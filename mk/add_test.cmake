enable_testing()

find_package(Boost 1.60 COMPONENTS unit_test_framework system program_options REQUIRED)
find_package(Sanitizers REQUIRED)

macro(adventofcode_add_test DAY_NAME)

    add_executable(${DAY_NAME} test.cpp)
    add_sanitizers(${DAY_NAME})
    target_include_directories(${DAY_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
    target_link_libraries(${DAY_NAME} ${Boost_LIBRARIES})
    
    add_test(NAME ${DAY_NAME}
        COMMAND ${DAY_NAME} --log_level=message
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

endmacro()