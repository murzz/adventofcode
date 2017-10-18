enable_testing()

find_package(Boost 1.60 COMPONENTS unit_test_framework system program_options REQUIRED)
find_package(Sanitizers REQUIRED)

macro(adventofcode_add_test DAY_NAME)

    add_executable(${DAY_NAME} test.cpp)
    add_sanitizers(${DAY_NAME})
    target_include_directories(${DAY_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
    target_link_libraries(${DAY_NAME} ${Boost_LIBRARIES})

    add_test(NAME ${DAY_NAME}
        COMMAND ${DAY_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        add_executable(${DAY_NAME}-fuzz fuzz.cpp)
        add_sanitizers(${DAY_NAME}-fuzz)
        target_include_directories(${DAY_NAME}-fuzz PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
        target_link_libraries(${DAY_NAME}-fuzz ${Boost_LIBRARIES})
        target_compile_options(${DAY_NAME}-fuzz PRIVATE "-fsanitize=fuzzer,address")

        add_test(NAME ${DAY_NAME}-fuzz
            COMMAND ${DAY_NAME}
        )
    endif()

endmacro()