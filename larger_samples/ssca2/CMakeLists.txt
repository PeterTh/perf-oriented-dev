cmake_minimum_required(VERSION 3.11)
project(perf_prog_npb_bt)

set_property(GLOBAL PROPERTY C_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c src/*.h src/sprng2.0/*.c src/sprng2.0/*.h)
include_directories(src/sprng2.0/include)

link_libraries(m)
add_definitions(-DLittleEndian, -DAdd__)

add_executable(ssca2 ${SOURCE_FILES})
