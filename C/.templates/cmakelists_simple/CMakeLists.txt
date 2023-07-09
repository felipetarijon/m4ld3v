cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(project_name LANGUAGES C VERSION 0.1)

set(CMAKE_BUILD_TYPE Debug) # Debug or Release

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
add_subdirectory(libs/log)