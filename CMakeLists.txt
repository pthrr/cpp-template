cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
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

add_compile_options(-Wall -Wextra -pedantic)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g3 -O0 -gsplit-dwarf)
    add_link_options(-Wl,-g -fuse-ld=gold)
  else()
    add_compile_options(-O3 -DNDEBUG)
    add_link_options(-flto)
  endif()
endif()

find_package(glog REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)
