#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "list.h"
#include "menu.h"
#include "notes_page.h"
#include "path.h"

WMENU* menus[4];

static void start_choose_cycle();
void init_notes_page();

int main ()
{
	initscr();
	
	init_notes_page();
	start_choose_cycle();
	
	getch();	
	endwin();		
}
void init_notes_page ()
{
	uint8_t qsize = COLS / 4; //quarter size

	uint8_t w = 40;
	uint8_t h = 16;

	//Years
	menus[0] = init_menu( h,                  w,
		                  (LINES - h) / 2 ,   (qsize * 0) + ( (qsize - w) / 2 ), 
						  0,                  0);
	// Months	
	menus[1] = init_menu( h,                  w,
			              (LINES - h) / 2,    (qsize * 1) + ( (qsize - w) / 2 ),
						  0,                  0);
	// Weeks	
	menus[2] = init_menu( h,                  w,
			              (LINES - h) / 2,    (qsize * 2) + ( (qsize - w) / 2 ), 
						  0,                  0);
	//Days	
	menus[3] = init_menu( h,                  w,
			              (LINES - h) / 2,    (qsize * 3) + ( (qsize - w) / 2 ), 
						  0,                  0);
		
}


static void start_choose_cycle()
{	
	PATH* dir_path;
	LIST* dir_list;
	WMENU* current_menu;
	MENU_TYPES current_dir_type = YEARS;
	uint8_t    user_choose = 0;

	dir_path = init_path();
	if ( !dir_path ) return;

	while ( 1 ) {
		mvwprintw(stdscr, 2, 2, "%s\n", dir_path->path);
		// need frees old dir list	
		current_menu = menus[current_dir_type];
		
		dir_list = read_dir_list(dir_path->path); 	
		set_list_menu(current_menu, dir_list);

		user_choose = choice_menu(current_menu);
		wrefresh(current_menu->win);	
		switch ( user_choose ) {
			case ( 0 ): // go back
				if ( current_dir_type == YEARS ) {
					// go to back page
					refresh();
					exit(1);	
				} 
				go_back_path(dir_path);
				--current_dir_type;
				break;
			/*
			case ( menus[current_dir_type]->n_choices - 1 ):
				if ( current_dir_type != YEARS ) {
					// system("vim goals.txt")
					break;
				}	
			*/
			default:	// go next					
				if ( current_dir_type == DAYS )	{
					char tmp[dir_path->max_size + 3 + 3];
					sprintf(tmp, "%s %s/%s",
							     "vim",
								 dir_path->path,
								 current_menu->choices[user_choose]);	
					system(tmp);
					break;
				}
				
				append_path(dir_path, current_menu->choices[user_choose]);	
				++current_dir_type;	
				break;
		}
	}
	//destroying all
}


void del_notes_page()
{
	
}







