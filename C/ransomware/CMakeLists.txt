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

# configuring dependencies
ExternalProject_Add(aes
  GIT_REPOSITORY "https://github.com/kokke/tiny-AES-c.git"
  GIT_TAG "f06ac37fc31dfdaca2e0d9bec83f90d5663c319b"
  PREFIX ${PROJECT_SOURCE_DIR}/libs/aes
  UPDATE_COMMAND ""
  INSTALL_COMMAND cmake --install . --prefix ${PROJECT_SOURCE_DIR}
  PATCH_COMMAND "")

ExternalProject_Get_Property(aes source_dir binary_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/googletest/include)
set(GMOCK_INCLUDE_DIR ${source_dir}/googlemock/include)

add_subdirectory(${source_dir} ${binary_dir})
add_subdirectory(libs/log)

# enable testing and define tests
# enable_testing()
# add_subdirectory(tests)