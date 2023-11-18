file(READ "${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp" VERSION_FILE)

string(REGEX MATCH "#define VERSION_MAJOR ([0-9]+)" _ ${VERSION_FILE})
set(VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#define VERSION_MINOR ([0-9]+)" _ ${VERSION_FILE})
set(VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#define VERSION_PATCH ([0-9]+)" _ ${VERSION_FILE})
set(VERSION_PATCH ${CMAKE_MATCH_1})

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
