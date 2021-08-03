cmake_minimum_required(VERSION 3.11)

set(CMAKE_VERBOSE_MAKEFILE ON)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.4)

FetchContent_MakeAvailable(Catch2)

set(TEST_FILES
        test_base.cpp
        test_functional.cpp
        test_subject.cpp
        test_combining.cpp
        test_buffers.cpp
        test_ring_buffer.cpp
        test_decoupler.cpp
        test_dsp.cpp
        )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(test test.cpp ${TEST_FILES})
target_link_libraries(test PRIVATE Catch2::Catch2 Threads::Threads urx)
