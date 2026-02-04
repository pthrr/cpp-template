add_subdirectory(common)

set(${PROJECT_NAME}_SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE ${RUST_LIB_NAME} spdlog::spdlog nlohmann_json::nlohmann_json
          CLI11::CLI11 trompeloeil::trompeloeil common::common)
