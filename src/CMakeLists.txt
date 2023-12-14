add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADER})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES logging.cppm)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
# target_sources(
#   ${PROJECT_NAME}
#   PRIVATE FILE_SET
#           all_my_modules
#           TYPE
#           CXX_MODULES
#           BASE_DIRS
#           ${PROJECT_SOURCE_DIR}
#           FILES
#           logging.cppm)
