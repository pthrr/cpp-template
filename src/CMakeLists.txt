add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADER})
target_link_libraries(${PROJECT_NAME} PRIVATE ${RUST_LIB_NAME} spdlog::spdlog nlohmann_json::nlohmann_json CLI11::CLI11)
target_include_directories(${PROJECT_NAME} PRIVATE "${RUST_HEADER_PATH}")
