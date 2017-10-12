include(ExternalProject)

# tarball
set(Boost_Version 1.65.1)
set(BOOST_SHA256 9807a5d16566c57fd74fb522764e0b134a8bbe6b6e8967b83afefd30dcd3be81)
set(BOOST_TARBALL_TYPE .tar.bz2)

string(REPLACE "." "_" Boost_Version_Underscore ${Boost_Version})
set(BOOST_URL1 "https://dl.bintray.com/boostorg/release/${Boost_Version}/source/boost_${Boost_Version_Underscore}${BOOST_TARBALL_TYPE}")
#set(BOOST_URL2 "http://sourceforge.net/projects/boost/files/boost/${Boost_Version}/boost_${Boost_Version_Underscore}${BOOST_TARBALL_TYPE}/download")

# modular boost
set(BOOST_REPO_URL https://github.com/boostorg/boost.git)
set(BOOST_TAG boost-1.62.0)


if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
   set(BOOST_TOOLSET gcc)
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
   set(BOOST_TOOLSET clang)
   set(BOOST_CXX_FLAGS "-stdlib=libc++")
   set(BOOST_LINK_FLAGS "-stdlib=libc++")
endif()

if(CMAKE_CROSSCOMPILING)
    set(BOOST_TOOLSET_TARGET arm)
else()
    set(BOOST_TOOLSET_TARGET x86_64)
endif()

set(BOOST_TOOLSET_TARGET ${CMAKE_SYSTEM_PROCESSOR})

set(BOOST_JAM_TOOLCHAIN
    "using ${BOOST_TOOLSET} : ${BOOST_TOOLSET_TARGET} : ${CMAKE_CXX_COMPILER}" # terminator ';' is printed via hex code below
)
MESSAGE(STATUS ${BOOST_JAM_TOOLCHAIN})

set(BOOST_CONFIGURE_PARAMS
   --prefix=${CMAKE_INSTALL_PREFIX}
#   --prefix=${STAGING_ROOT}
   --with-libraries=system,program_options,test
)

set(BOOST_CONFIGURE_COMMAND ./bootstrap.sh ${BOOST_CONFIGURE_PARAMS} && /bin/echo -e ${BOOST_JAM_TOOLCHAIN} \\x3b >> project-config.jam)

set(BOOST_BUILD_PARAMS
# for modular boost
#    headers
    toolset=${BOOST_TOOLSET}-${BOOST_TOOLSET_TARGET}
# Suppress all informational messages    
    -d0
#    link=static
    variant=release
#    threading=single
#    runtime-link=shared
)

if(BOOST_CXX_FLAGS)
   set(BOOST_BUILD_PARAMS ${BOOST_BUILD_PARAMS} cxxflags="${BOOST_CXX_FLAGS}")
endif()

if(BOOST_LINK_FLAGS)
   set(BOOST_BUILD_PARAMS ${BOOST_BUILD_PARAMS} linkflags="${BOOST_LINK_FLAGS}")
endif()

#include(ProcessorCount)
#ProcessorCount(N)
#if(NOT N EQUAL 0)
#  set(BOOST_BUILD_PARAMS ${BOOST_BUILD_PARAMS} -j${N})
#endif()


set(BOOST_BUILD_COMMAND ./b2 ${BOOST_BUILD_PARAMS})

set(BOOST_INSTALL_PARAMS
   ${BOOST_BUILD_PARAMS}
   install
)
set(BOOST_INSTALL_COMMAND ./b2 ${BOOST_INSTALL_PARAMS})

ExternalProject_Add(boost
#    GIT_REPOSITORY ${BOOST_REPO_URL}
#    GIT_TAG ${BOOST_TAG}
#    URL ${BOOST_URL1} ${BOOST_URL2}
    URL ${BOOST_URL1}
    URL_HASH SHA256=${BOOST_SHA256}
    CONFIGURE_COMMAND ${BOOST_CONFIGURE_COMMAND}
    BUILD_COMMAND ${BOOST_BUILD_COMMAND}
    BUILD_IN_SOURCE TRUE
    INSTALL_COMMAND ${BOOST_INSTALL_COMMAND}
#    LOG_DOWNLOAD TRUE
#    LOG_UPDATE TRUE
#    LOG_CONFIGURE TRUE
#    LOG_BUILD TRUE
#    LOG_TEST TRUE
#    LOG_INSTALL TRUE
)
