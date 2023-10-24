cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
cmake_policy(SET CMP0100 NEW) # handle .hh files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conan)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectVersion.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectSettings.cmake)

project(
  my_project
  LANGUAGES C CXX
  VERSION ${VERSION}
  DESCRIPTION "My project")
message(STATUS "${PROJECT_NAME} version is: ${VERSION}")

find_package(glog REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh)
file(GLOB_RECURSE ${PROJECT_NAME}_TESTS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)
