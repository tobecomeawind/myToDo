#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "list.h"
#include "menu.h"
#include "notes_page.h"
#include "path.h"

WMENU* menus[COUNT_MENUS];


static void init_menus();
static void init_cycle_notes_page();
inline static void del_menus();

void init_notes_page ()
{	
	init_menus();
	init_cycle_notes_page();	
}

static void init_menus ()
{
	uint8_t qsize = COLS / 4; //quarter size

	uint8_t w = 40;
	uint8_t h = 16;

	
	for ( int i = 0; i < COUNT_MENUS; i++ ) 
		menus[i] = init_menu(h,               w, 
				            (LINES - h) / 2, (qsize * i) + ((qsize - w) / 2),
							 NULL);			
}

inline static void del_menus()
{
	for ( int i = 0; i < COUNT_MENUS; i++ ) del_menu(menus[i]);
}

static void init_cycle_notes_page ()
{	
	PATH* dir_path;
	LIST* dir_list;
	WMENU* current_menu;
	MENU_TYPES current_dir_type = YEARS;
	uint8_t    user_choice = 0;

	dir_path = init_path();
	if ( !dir_path ) return;

	while ( 1 ) {
		mvwprintw(stdscr, 2, 2, "%s\n", dir_path->path);
		current_menu = menus[current_dir_type];
		
		dir_list = init_from_dir_list(dir_path->path); 	
		
		del_list(current_menu->choices);	
		set_list_menu(current_menu, dir_list);

		user_choice = choice_menu(current_menu);
		wrefresh(current_menu->win);	
		switch ( user_choice ) {
			case ( 0 ): // Back
				if ( current_dir_type == YEARS ) {
					del_path(dir_path);
					del_notes_page();	
					return;	
				} 
				go_back_path(dir_path);
				--current_dir_type;
				break;
			case ( 1 ):
				if ( current_dir_type != YEARS ) {
					char tmp[dir_path->max_size + 3 + 9];
					sprintf(tmp, "%s %s/%s",
							     "vim",
								 dir_path->path,
								 "goals.txt");	
					system(tmp);
					refresh();
					break;
				}	
			default:	// go next					
				if ( current_dir_type == DAYS )	{
					char tmp[dir_path->max_size + 3 + 3];
					sprintf(tmp, "%s %s/%s",
							     "vim",
								 dir_path->path,
								 current_menu->choices->list[user_choice]);	
					system(tmp);
					refresh();
					break;
				}
				
				append_path(dir_path, current_menu->choices->list[user_choice]);	
				++current_dir_type;	
				break;
		}
	}
	//destroying all
}


void del_notes_page()
{
	del_menus();	
}







