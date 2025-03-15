cmake_minimum_required(VERSION 3.22)
project(Coppermind LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Parallel compilation on Windows
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.0
)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

FetchContent_MakeAvailable(Catch2)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
include(GoogleTest)

add_subdirectory(Source)