#include "menu.h"
#include <stdlib.h>


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
	print_menu_iml(menu);	

	while ( 1 ) {
		ch = wgetch(menu->win);	
		switch ( ch ) {
			case KEY_UP:
				if ( menu->current == 1 )
					menu->current = menu->n_choices;
				else
					--menu->current;
				break;
			case KEY_DOWN:	
				if ( menu->current == menu->n_choices )
					menu->current = 1;
				else
					++menu->current;
				break;
			case 10: //Enter
				curs_set(1);	
				return menu->current;
		}	
		print_menu_iml(menu);
	}	

}


WMENU* init_menu ( uint8_t height,  uint8_t weight,
                   uint8_t starty,  uint8_t startx,
                   char**  choices, uint8_t n_choices)
{
	WMENU*  menu;	
	WINDOW* win;

	menu = (WMENU*) malloc(sizeof(WMENU));
	
	win = newwin(height, weight, starty, startx);
	
	if ( !(win && choices && n_choices) )
		return NULL;

	menu->win       = win;
	menu->choices   = choices;
	menu->n_choices = n_choices;
	menu->current   = 1;

	return menu;
}

void del_menu ( WMENU* menu )
{
	wborder(menu->win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(menu->win);
	delwin(menu->win);
	refresh();
	// free(menu->choices);

	free(menu);	
}


static void print_menu_iml ( WMENU* menu )
{
	uint8_t x, y;
	
	x = y = 2;	
	
	box(menu->win, 0, 0);	
	for ( int i = 0; i < menu->n_choices; i++ ) {
		if ( menu->current == i + 1 ) {
			wattron(menu->win,  A_REVERSE);
			mvwprintw(menu->win, y + i, x, "%s", menu->choices[i]);	
			wattroff(menu->win, A_REVERSE);
		} else 	
			mvwprintw(menu->win, y + i, x, "%s", menu->choices[i]);	
	}
	wrefresh(menu->win);	
}




