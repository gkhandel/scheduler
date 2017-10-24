cmake_minimum_required (VERSION 3.2)

find_package(Threads REQUIRED)
include(../config/gtest.cmake)

add_subdirectory(scheduler)
