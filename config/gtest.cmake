include(ExternalProject)

ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.7.0.zip
    URL_HASH SHA1=f89bc9f55477df2fde082481e2d709bfafdb057b
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googletest source_dir binary_dir)
include_directories("${source_dir}/include")

add_library(gtest      STATIC IMPORTED)
set_target_properties(gtest PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/libgtest.a
)

add_library(gtest_main STATIC IMPORTED)
set_target_properties(gtest_main PROPERTIES
    IMPORTED_LOCATION ${binary_dir}/libgtest_main.a
)

if (NOT ${CMAKE_THREAD_LIBS_INIT} EQUAL "")
    set_target_properties(gtest PROPERTIES
        IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
    )
    set_target_properties(gtest_main PROPERTIES
        IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
    )
endif()

add_dependencies(gtest      googletest)
add_dependencies(gtest_main googletest)
