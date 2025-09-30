cmake_minimum_required( VERSION 3.10 )
set(CMAKE_BUILD_TYPE Debug)

project( main )

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR} )
include_directories( src/datatypes )
include_directories( src/ui )
include_directories( src/ui/widgets )
include_directories( src/ui/pages )

# Datatypes
add_library(list_lib
	src/datatypes/list.c
	src/datatypes/list.h
)

add_library(path_lib
	src/datatypes/path.c
	src/datatypes/path.h
)

# Widgets
add_library(menu_ui_lib
	src/ui/widgets/menu.c
	src/ui/widgets/menu.h
)

#Pages
add_library(page_changer_lib
	src/ui/pages/page_changer.c
	src/ui/pages/page_changer.h
)

add_library(notes_page_ui_lib
	src/ui/pages/notes_page.c
	src/ui/pages/notes_page.h
)
target_link_libraries(notes_page_ui_lib 
	list_lib 
	path_lib)

add_library(main_page_ui_lib
	src/ui/pages/main_page.c
	src/ui/pages/main_page.h
)
target_link_libraries(main_page_ui_lib 
	notes_page_ui_lib 
	menu_ui_lib
	page_changer_lib)



add_executable( ${PROJECT_NAME} src/main.c )

target_link_libraries( ${PROJECT_NAME} ${CURSES_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} list_lib )
target_link_libraries( ${PROJECT_NAME} path_lib )
target_link_libraries( ${PROJECT_NAME} menu_ui_lib )
target_link_libraries( ${PROJECT_NAME} notes_page_ui_lib )
target_link_libraries( ${PROJECT_NAME} main_page_ui_lib )

