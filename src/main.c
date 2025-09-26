#include <stdio.h>
#include <ncurses.h>
#include <stdint.h>
#include "menu.h"



int main ( int argc, char* argv[] )
{
	WMENU* menu;	
	uint8_t i, w, h; 

	h = 10;
	w = 10;

	initscr();
	clear();
		
	char* list[] = {"First", "Second", "Third"};
	
	menu = init_menu(h, w, (LINES - h) / 2, (COLS - w) / 2, (char**)list, 3);

	if ( !menu ) {
		printf("Menu not created !!!");
		return -1;	
	}

	i = choice_menu(menu);	

	del_menu(menu);
	
	mvwprintw(stdscr, (LINES - 10) / 2, COLS / 2, "You choose: %s\n", list[i - 1]);	

	getch();
	endwin();
	return 0;	
}


