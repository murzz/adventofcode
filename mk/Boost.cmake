
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    find_package(Boost 1.60 COMPONENTS unit_test_framework program_options REQUIRED)
endif()