add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADER})
target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
target_include_directories(${PROJECT_NAME} PUBLIC ${glog_INCLUDE_DIR})
