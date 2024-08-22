cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectVersion.cmake)

project(
  my_project
  LANGUAGES C CXX
  VERSION ${PROJECT_VERSION}
  DESCRIPTION "My project")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectSettings.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/RustSettings.cmake)

add_library(${RUST_LIB_NAME} STATIC IMPORTED)
set_target_properties(${RUST_LIB_NAME} PROPERTIES
    IMPORTED_LOCATION "${RUST_LIB_PATH}/lib${RUST_LIB_NAME}.a"
    INTERFACE_INCLUDE_DIRECTORIES "${RUST_HEADER_PATH}"
)

find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(CLI11 REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/build/compile_commands.json
)
