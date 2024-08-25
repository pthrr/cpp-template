set(RUST_LIB_NAME "rust")
set(RUST_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/rust/target/${BUILD_TYPE_LOWER}")
set(RUST_HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/rust/target/cxxbridge/${RUST_LIB_NAME}/src")

if(BUILD_TYPE_LOWER STREQUAL "release")
    set(CARGO_CMD "cargo" "build" "--release")
elseif(BUILD_TYPE_LOWER STREQUAL "debug")
    set(CARGO_CMD "cargo" "build")
else()
    message(FATAL_ERROR "Unsupported build type: ${BUILD_TYPE_LOWER}")
endif()

execute_process(
    COMMAND ${CARGO_CMD}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/rust"
    RESULT_VARIABLE CARGO_BUILD_RESULT
    OUTPUT_VARIABLE CARGO_BUILD_OUTPUT
    ERROR_VARIABLE CARGO_BUILD_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT CARGO_BUILD_RESULT EQUAL 0)
    message(FATAL_ERROR "Cargo build failed: ${CARGO_BUILD_ERROR}")
else()
    message(STATUS "Cargo build succeeded: ${CARGO_BUILD_OUTPUT}")
endif()

add_library(${RUST_LIB_NAME} STATIC IMPORTED GLOBAL)
set_target_properties(${RUST_LIB_NAME} PROPERTIES
    IMPORTED_LOCATION "${RUST_LIB_PATH}/lib${RUST_LIB_NAME}.a"
    INTERFACE_INCLUDE_DIRECTORIES "${RUST_HEADER_PATH}"
)

add_subdirectory(cpp)
