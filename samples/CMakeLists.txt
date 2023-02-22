cmake_minimum_required(VERSION 3.10)
project(perf_oriented_prog_samples)

set_property(GLOBAL PROPERTY C_STANDARD 11)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(mmul mmul/mmul.c)

add_executable(delannoy delannoy/delannoy.c)

add_executable(nbody nbody/nbody.c)
target_link_libraries(nbody m)

add_executable(qap qap/qap.c)

add_executable(filesearch filesearch/filesearch.c)

add_executable(filegen filegen/filegen.c)
