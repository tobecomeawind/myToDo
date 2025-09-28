#include <stdio.h>
#include <ncurses.h>
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
	LIST* list;
	list = read_dir_list("/home/tobecomeawind/pain/what_is_it/data");
	uint8_t qsize = COLS / 4; //quarter size
	if ( !list ) return;	

	uint8_t w = 40;
	uint8_t h = 16;

	insert_list(list, 0, "Back");
	//Years
	menus[0] = init_menu( h,                  w,
		                  (LINES - h) / 2 ,   (qsize * 0) + ( (qsize - w) / 2 ), 
						  list->list,         list->size - 1);
	list = read_dir_list("/home/tobecomeawind/pain/what_is_it/data/2025");
	insert_list(list, 0, "Back");
	// Months	
	menus[1] = init_menu( h,                  w,
			              (LINES - h) / 2,    (qsize * 1) + ( (qsize - w) / 2 ),
						  list->list,         list->size - 1);
	list = read_dir_list("/home/tobecomeawind/pain/what_is_it/data/2025/9");
	insert_list(list, 0, "Back");
	// Weeks	
	menus[2] = init_menu( h,                  w,
			              (LINES - h) / 2,    (qsize * 2) + ( (qsize - w) / 2 ), 
						  list->list,         list->size - 1);
	list = read_dir_list("/home/tobecomeawind/pain/what_is_it/data/2025/9/4");
	insert_list(list, 0, "Back");
	//Days	
	menus[3] = init_menu( h,                  w,
			              (LINES - h) / 2,    (qsize * 3) + ( (qsize - w) / 2 ), 
						  list->list,         list->size - 1);
		
}


static void start_choose_cycle()
{	
	PATH* dir_path;
	MENU_TYPES current_dir_type = YEARS;
	uint8_t    user_choose = 0;

	dir_path = init_path();
	if ( !dir_path ) return;

	while ( 1 ) {
		user_choose = choice_menu(menus[current_dir_type]);
		switch ( user_choose ) {
			case ( 0 ): // go back
				if ( current_dir_type == YEARS ) {
					// go to back page	
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
					// system("vim path");
					break;
				}
				
				append_path(dir_path, 
						    menus[current_dir_type]->choices[user_choose]);
				++current_dir_type;	
				break;
		}
	}
	//destroying all
}


void del_notes_page()
{
	
}







