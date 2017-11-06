set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMMON_GCC_CXX_FLAGS
    -pedantic
    -Wall
    -Wextra
)

set(COMMON_CLANG_CXX_FLAGS
#    -stdlib=libc++
    -pedantic
    -Wall
    -Wextra
)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(COMMON_CXX_FLAGS ${COMMON_GCC_CXX_FLAGS})
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(COMMON_CXX_FLAGS ${COMMON_CLANG_CXX_FLAGS})
endif()