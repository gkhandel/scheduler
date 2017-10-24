include(ExternalProject)

ExternalProject_Add(
    date
    URL https://github.com/HowardHinnant/date/archive/2.1.0.zip
    URL_HASH SHA1=e40c98b324431fda563f0b4ab7ea8ce93e1e053c
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/date
    # Disable install step
    CONFIGURE_COMMAND ""
    CMAKE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(date source_dir binary_dir)
include_directories("${source_dir}")
