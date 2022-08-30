# REFERENCE:
# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# set the project name
project(m4ld3v VERSION 0.1)

include(GNUInstallDirs)
include(ExternalProject)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# defines targets and sources
add_subdirectory(src)

# contains an "external" library we will link to
add_subdirectory(libs/log)
add_subdirectory(libs/aes)

# enable testing and define tests
# enable_testing()
# add_subdirectory(tests)