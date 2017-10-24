cmake_minimum_required (VERSION 3.2)
project(scheduler)

file(GLOB_RECURSE scheduler_source "*/*.cpp")

add_library(scheduler_lib ${scheduler_source})

add_executable(scheduler "main.cpp")

target_link_libraries(scheduler scheduler_lib proto ${dependency_libraries})
