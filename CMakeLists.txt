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
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_subdirectory(Source)