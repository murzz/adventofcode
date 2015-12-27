include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
endif()

set(CLANG_DISABLED_WARNINGS "${CLANG_DISABLED_WARNINGS} -Wno-c++98-compat") # targeted to c++1y
set(CLANG_DISABLED_WARNINGS "${CLANG_DISABLED_WARNINGS} -Wno-global-constructors") # warnings that global constructor is slowing down app startup,
                                                                                   # it is used in boost.test, thus disabling
set(CLANG_DISABLED_WARNINGS "${CLANG_DISABLED_WARNINGS} -Wno-missing-prototypes") # it is forcing prototypes for every non inline function,
                                                                                  # too lazy for this

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Weverything ${CLANG_DISABLED_WARNINGS}")
endif()