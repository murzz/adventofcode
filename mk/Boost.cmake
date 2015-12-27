
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()