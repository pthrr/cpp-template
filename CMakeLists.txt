cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectVersion.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectSettings.cmake)

project(
  my_project
  LANGUAGES C CXX
  VERSION ${PROJECT_VERSION}
  DESCRIPTION "My project")

find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
# target_sources(
#   my_app
#   PRIVATE FILE_SET
#           all_my_modules
#           TYPE
#           CXX_MODULES
#           BASE_DIRS
#           ${PROJECT_SOURCE_DIR}
#           FILES
#           logging.cppm)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)
