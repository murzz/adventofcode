include(ExternalProject)

set(CMAKE_REPO_URL https://cmake.org/cmake.git)
set(CMAKE_TAG "v3.9.5")

set(CMAKE_BUILD_ARGS 
    -DCMAKE_USE_OPENSSL=ON
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)

ExternalProject_Add(
        cmake-${CMAKE_TAG}
        GIT_REPOSITORY ${CMAKE_REPO_URL}
        GIT_TAG ${CMAKE_TAG}
        CMAKE_ARGS ${CMAKE_BUILD_ARGS}
        LOG_DOWNLOAD TRUE
        LOG_UPDATE TRUE
        LOG_CONFIGURE TRUE
        LOG_BUILD TRUE
        LOG_TEST TRUE
        LOG_INSTALL TRUE
)
