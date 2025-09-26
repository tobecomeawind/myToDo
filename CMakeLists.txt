cmake_minimum_required( VERSION 3.10 )

set(CMAKE_BUILD_TYPE Debug)

project( main )

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR} )
include_directories( src/ui)


add_library(menu_UI
	src/ui/menu.c
	src/ui/menu.h
)

add_executable( ${PROJECT_NAME} src/main.c )

target_link_libraries( ${PROJECT_NAME} ${CURSES_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} menu_UI )

