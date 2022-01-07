cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR)

macro(create_test FILENAME)
    add_executable(tst_${FILENAME} ${FILENAME}.c)
    add_test(tst_${FILENAME} tst_${FILENAME})
    target_link_libraries(tst_${FILENAME} gridDesigner)
endmacro()

create_test(zzGridTest)

find_program(valgrindPresent "valgrind")
find_program(xmllintPresent "xmllint")

if(valgrindPresent AND xmllintPresent)
    message("Run mem-tests")
    add_test(NAME tst_leakcheck COMMAND ${CMAKE_CURRENT_LIST_DIR}/assertNoMemoryLeaks.sh ${CMAKE_CURRENT_BINARY_DIR})
endif()
