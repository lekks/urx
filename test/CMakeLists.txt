cmake_minimum_required(VERSION 3.11)

set(CMAKE_VERBOSE_MAKEFILE ON)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.4)

FetchContent_MakeAvailable(Catch2)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2)
