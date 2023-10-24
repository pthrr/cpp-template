enable_testing()
option(INSTALL_GTEST
       "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG main
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_tests ${${PROJECT_NAME}_TESTS})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE GTest::gtest_main glog::glog)

target_include_directories(${PROJECT_NAME}_tests PUBLIC ${glog_INCLUDE_DIR})

set_target_properties(${PROJECT_NAME}_tests PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
