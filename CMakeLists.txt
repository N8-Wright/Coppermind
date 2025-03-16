cmake_minimum_required(VERSION 3.22)
project(Coppermind LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Parallel compilation on Windows
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

Include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
set_target_properties(gtest PROPERTIES FOLDER "Vendor")
set_target_properties(gtest_main PROPERTIES FOLDER "Vendor")
set_target_properties(gmock PROPERTIES FOLDER "Vendor")
set_target_properties(gmock_main PROPERTIES FOLDER "Vendor")

include(CTest)
include(GoogleTest)

add_subdirectory(Source)