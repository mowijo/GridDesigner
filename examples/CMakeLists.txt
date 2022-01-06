cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR)


macro( add_example NAME)

    add_executable(${NAME} ${NAME}.c)
    target_link_libraries(${NAME} gridDesigner)
endmacro()

add_example(zzGridExample)
