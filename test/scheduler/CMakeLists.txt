cmake_minimum_required (VERSION 3.2)
project(scheduler_test)

file(GLOB_RECURSE source "*.cpp")
add_executable(scheduler_test ${source})

target_link_libraries(scheduler_test scheduler_lib gtest gtest_main proto ${dependency_libraries})

add_test(NAME scheduler_test
         COMMAND scheduler_test)
