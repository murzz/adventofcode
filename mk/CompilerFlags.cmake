set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wextra")
endif()

set(CLANG_DISABLED_WARNINGS "${CLANG_DISABLED_WARNINGS} -Wno-c++98-compat") # targeted to c++1y
set(CLANG_DISABLED_WARNINGS "${CLANG_DISABLED_WARNINGS} -Wno-global-constructors") # warnings that global constructor is slowing down app startup,
                                                                                   # it is used in boost.test, thus disabling
set(CLANG_DISABLED_WARNINGS "${CLANG_DISABLED_WARNINGS} -Wno-missing-prototypes") # it is forcing prototypes for every non inline function,
                                                                                  # too lazy for this
set(CLANG_DISABLED_WARNINGS "${CLANG_DISABLED_WARNINGS} -Wno-missing-braces -Wno-c++98-compat -Wno-c++98-compat-pedantic")                                                                                 

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Weverything ${CLANG_DISABLED_WARNINGS}")
endif()
