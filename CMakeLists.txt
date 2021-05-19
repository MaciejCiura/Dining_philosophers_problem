cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD ON)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

add_executable(untitled main.cpp Philosopher.cpp Philosopher.h)

if(TARGET Threads::Threads)
    target_link_libraries(untitled PRIVATE Threads::Threads ${CURSES_LIBRARIES})
endif()