cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )
project(GridDesigner LANGUAGES C)

include (CTest)

add_subdirectory(lib)
add_subdirectory(examples)
add_subdirectory(tests)
