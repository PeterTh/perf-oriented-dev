cmake_minimum_required(VERSION 3.10)
project(perf_oriented_prog_tools)

set_property(GLOBAL PROPERTY C_STANDARD 11)

find_package(OpenMP)
if(OpenMP_C_FOUND)
    link_libraries(OpenMP::OpenMP_C)
endif()

link_libraries(m pthread)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(loadcapture load_generator/loadcapture.c)
add_executable(loadgen load_generator/loadgen.c)
add_executable(loadprofile load_generator/loadprofile.c)
add_executable(loadtest load_generator/loadtest.c)

add_executable(malloctest malloctest/malloctest.c)
