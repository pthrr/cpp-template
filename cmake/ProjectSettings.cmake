message(STATUS "build type is: ${CMAKE_BUILD_TYPE}")

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(MOLD_LINKER mold)
find_program(GOLD_LINKER gold)

if(MOLD_LINKER)
  add_link_options("-fuse-ld=mold")
  message(STATUS "Using mold as linker")
elseif(GOLD_LINKER)
  add_link_options("-fuse-ld=gold")
  message(STATUS "Using gold as linker")
else()
  message(STATUS "Default linker will be used")
endif()

add_compile_options(-Wall -Wextra -pedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-g3 -O0 -gsplit-dwarf)
else()
  add_compile_options(-O3 -DNDEBUG)
  add_link_options(-flto)
endif()
