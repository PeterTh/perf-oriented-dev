cmake_minimum_required(VERSION 3.10)
project(perf_oriented_prog_samples)
add_executable(mmul mmul/mmul.c)
set_property(TARGET mmul PROPERTY C_STANDARD 11)
