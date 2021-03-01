cmake_minimum_required(VERSION 3.5)

set(LIB_NAME nnoops-containers)
set(VERSION 0.1)


project(${LIB_NAME} VERSION ${VERSION} LANGUAGES C CXX)

include(GNUInstallDirs)
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(cmake/functions.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(CLANG_TIDY   "Enable clang-tidy checks during compilation" OFF)
option(ASAN         "Enable Address Sanitizer" OFF)
option(TSAN         "Enable Thread Sanitizer" OFF)
option(UBSAN        "Enable Undefined Behavior Sanitizer" OFF)


if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "^(AppleClang|Clang|GNU)$")
    add_compile_options(-Werror)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(/bigobj)
    add_compile_options(/WX)
endif()

include_directories(src)

include(cmake/gtest.cmake)
enable_testing()
add_subdirectory(test)

if(CLANG_TIDY)
    include(cmake/clang-tidy.cmake)
endif()

if(ASAN)
    include(cmake/asan.cmake)
endif()

if(TSAN)
    include(cmake/tsan.cmake)
endif()

if(UBSAN)
    include(cmake/ubsan.cmake)
endif()