#include <ncurses.h>
#include "main_page.h"
#include "menu.h"



int main ( int argc, char* argv[] )
{
	initscr();
	init_main_page();
	endwin();	
	
	return 0;	
}


