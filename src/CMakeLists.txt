add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADER})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog nlohmann_json::nlohmann_json CLI11::CLI11)

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E create_symlink
#     ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/compile_commands.json
#     ${CMAKE_SOURCE_DIR}/compile_commands.json
# )
