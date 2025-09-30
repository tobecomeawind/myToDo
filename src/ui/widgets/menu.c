#include <stdlib.h>

#include "menu.h"

/* На вход получаем список пунктов меню, отрисовываем и возвращаем индекс
 * выбранного пункта*/

static void print_menu_iml ( WMENU* menu );

uint8_t choice_menu ( WMENU* menu )
{
	int ch;
	curs_set(0);
	cbreak();
	keypad(menu->win, TRUE);
	clear();
	noecho();

	menu->current = 1;
	print_menu_iml(menu);	

	while ( 1 ) {
		ch = wgetch(menu->win);	
		switch ( ch ) {
			case KEY_UP:
				if ( menu->current == 1 )
					menu->current = menu->choices->size - 1;
				else
					--menu->current;
				break;
			case KEY_DOWN:	
				if ( menu->current == menu->choices->size - 1 )
					menu->current = 1;
				else
					++menu->current;
				break;
			case 10: //Enter
				curs_set(1);	
				wclear(menu->win);
				return menu->current - 1;
		}	
		print_menu_iml(menu);
	}	

}

WMENU* init_menu ( uint8_t height,  uint8_t weight,
                   uint8_t starty,  uint8_t startx,
                   LIST* lp)
{
	WMENU*  menu;	
	WINDOW* win;

	menu = (WMENU*) malloc(sizeof(WMENU));
	
	win = newwin(height, weight, starty, startx);
	
	if ( !win )
		return NULL;

	menu->win       = win;
	menu->choices   = lp;
	menu->current   = 1;

	return menu;
}

void del_menu ( WMENU* menu )
{
	wborder(menu->win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(menu->win);
	delwin(menu->win);
	refresh();
	del_list(menu->choices);

	free(menu);	
}

void set_list_menu ( WMENU* menu, LIST* list)
{
	if ( !menu || !list ) return;	
	// delete old?
	menu->choices = list;
}

static void print_menu_iml ( WMENU* menu )
{
	uint8_t x, y;
	
	x = y = 2;	
	
	box(menu->win, 0, 0);	
	for ( int i = 0; i < menu->choices->size - 1; i++ ) {
		if ( menu->current == i + 1 ) {
			wattron(menu->win,  A_REVERSE);
			mvwprintw(menu->win, y + i, x, "%s", menu->choices->list[i]);	
			wattroff(menu->win, A_REVERSE);
		} else 	
			mvwprintw(menu->win, y + i, x, "%s", menu->choices->list[i]);	
	}
	wrefresh(menu->win);	
}




