cmake_minimum_required(VERSION 3.12)

project("bosswestfalen::runtime_array"
        VERSION 0.3.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic")

if(NOT "${CMAKE_BUILD_TYPE}")
    message(STATUS "Build type not specified -> changed to DEBUG")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -O3 -DNDEBUG")
endif()


set(BWF_TARGET_NAME "runtime_array")

add_library(${BWF_TARGET_NAME} INTERFACE)

target_include_directories(${BWF_TARGET_NAME}
                           INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)

target_compile_features(${BWF_TARGET_NAME}
                        INTERFACE
                        cxx_std_17)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include)

option(BUILD_TESTS
       "Build tests"
       ON)

option(BUILD_DOCS
       "Build doxygen documentation"
       OFF)

option(BUILD_CODEANALYSIS
       "Use clang-tidy to analyse code"
       OFF)


if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(unit-test)
endif()


if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(DOXYGEN_FULL_PATH_NAMES "YES")
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_SOURCE_DIR}/include)
    doxygen_add_docs(docs ${CMAKE_SOURCE_DIR}/include)
endif()

if(BUILD_CODEANALYSIS)
    find_program(CLANG_TIDY clang-tidy)
    if(${CLANG_TIDY} STREQUAL "CLANG_TIDY-NOTFOUND")
        message(FATAL_ERROR "Code analysis enabled, but clang-tidy not available!")
    endif()

    add_custom_target(codeanalysis
                      COMMAND clang-tidy
                      -checks=*,-llvm-header-guard,-fuchsia-trailing-return,-fuchsia-overloaded-operator,-cppcoreguidelines-pro-type-const-cast
                      ${CMAKE_SOURCE_DIR}/include/bosswestfalen/runtime_array.hpp
                      -extra-arg=-std=c++17)
endif()

