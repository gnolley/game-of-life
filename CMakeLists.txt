cmake_minimum_required(VERSION 3.26.4)

project(
    game-of-life
    VERSION 0.0.1
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD              23)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(SHARED_INCLUDES ${CMAKE_SOURCE_DIR}/shared)

set(GAME_EXECUTABLE GameOfLife)
set(GAME_DIR ${CMAKE_SOURCE_DIR}/game)

set(SIM_TARGET GoL-Simulation)
set(SIM_DIR ${CMAKE_SOURCE_DIR}/simulation)

set(RENDERER_TARGET GoL-Renderer)
set(RENDERER_DIR ${CMAKE_SOURCE_DIR}/renderer)

option(BUILD_UNIT_TESTS "Build unit tests with build" OFF)
option(ENABLE_WARNINGS "Build unit tests with build" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Build unit tests with build" ON)

option(ENABLE_LTO "Enable Link Time Optimisation" OFF)


if(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitiser" ON)
option(ENABLE_SANITIZE_UNDEF "Enable Undefined Sanitiser" ON)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitiser" OFF)
option(ENABLE_SANITIZE_UNDEF "Enable Undefined Sanitiser" OFF)

endif()

include ($ENV{VCPKG_ROOT}\\scripts\\buildsystems\\vcpkg.cmake)
include(ConfigSafeGuard)
include(Utils)

#find_package(glfw3 CONFIG REQUIRED)

if(${ENABLE_SANITIZE_ADDR} OR ${ENABLE_SANITIZE_UNDEF})
    include(Sanitisers)
    add_santiser_flags()
endif()

add_subdirectory(simulation)
add_subdirectory(renderer)
add_subdirectory(game)

