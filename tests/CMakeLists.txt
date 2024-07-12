include(CTest)
include(Catch)

set(TEST_SANITIZER_FLAGS "-fsanitize=address,undefined,thread,memory,leak,safe-stack")
file(GLOB TEST_SOURCES "*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME} PRIVATE spdlog::spdlog Catch2::Catch2WithMain)
  add_compile_options(${TEST_NAME} PRIVATE ${TEST_SANITIZER_FLAGS})
  add_link_options(${TEST_NAME} PRIVATE ${TEST_SANITIZER_FLAGS})
  catch_discover_tests(${TEST_NAME})
endforeach()
