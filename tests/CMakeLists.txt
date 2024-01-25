include(CTest)
include(Catch)

file(GLOB TEST_SOURCES "*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME} PRIVATE spdlog::spdlog Catch2::Catch2WithMain)
  target_compile_options(${TEST_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)
  target_link_options(${TEST_NAME} PRIVATE -fsanitize=address)
  catch_discover_tests(${TEST_NAME})
endforeach()
