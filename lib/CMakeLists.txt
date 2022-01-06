cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR)

project( gridDesigner  VERSION 1.0.0 LANGUAGES C )

add_library( ${PROJECT_NAME} STATIC
	src/ZigZagGrid.c
)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
	m
)

target_include_directories( ${PROJECT_NAME} PUBLIC include )
