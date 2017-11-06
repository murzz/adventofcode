enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Sanitizers)

function(adventofcode_add_test DAY_NAME)

    add_executable(${DAY_NAME} test.cpp)
    add_sanitizers(${DAY_NAME})
    target_include_directories(${DAY_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${DAY_NAME} Boost::unit_test_framework)
    target_compile_options(${DAY_NAME} PRIVATE ${COMMON_CXX_FLAGS})

    add_test(NAME ${DAY_NAME}
        COMMAND ${DAY_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    if(SANITIZE_FUZZER)
        add_executable(${DAY_NAME}-fuzz fuzz.cpp)
        add_sanitizers(${DAY_NAME}-fuzz)
        target_include_directories(${DAY_NAME}-fuzz PRIVATE ${CMAKE_SOURCE_DIR})
        target_link_libraries(${DAY_NAME}-fuzz Boost::unit_test_framework)
        target_compile_options(${DAY_NAME}-fuzz PRIVATE ${COMMON_CXX_FLAGS})

        add_test(NAME ${DAY_NAME}-fuzz
            COMMAND ${DAY_NAME}-fuzz
        )
    endif()

endfunction()