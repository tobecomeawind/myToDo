#include <stdlib.h>
#include <string.h>

#include "menu.h"

/* На вход получаем список пунктов меню, отрисовываем и возвращаем индекс
 * выбранного пункта*/

static void print_menu_iml ( WMENU* menu );
static char* set_title_iml ( WMENU* menu, char* title );

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

WMENU* init_menu ( uint8_t height,  uint8_t   weight,
                   uint8_t starty,  uint8_t   startx,
				   char*   title,   TITLE_POS title_pos,
                   LIST* lp)
{
	WMENU*  menu;	
	WINDOW* win;

	menu = (WMENU*) malloc(sizeof(WMENU));
	
	win = newwin(height, weight, starty, startx);
	
	if ( !win )
		return NULL;
	
	menu->h = height;
	menu->w = weight;
	menu->y = starty;
	menu->x = startx;		

	menu->win       = win;
	
	menu->choices   = lp;
	menu->current   = 1;
	menu->title_pos = title_pos;
	set_title(menu, title);


	return menu;
}

void del_menu ( WMENU* menu )
{
	wborder(menu->win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(menu->win);
	delwin(menu->win);
	refresh();
	del_list(menu->choices);
	free(menu->title);
	free(menu);	
}

void set_list_menu ( WMENU* menu, LIST* list)
{
	if ( !menu || !list ) return;	
	del_list(menu->choices);	
	menu->choices = list;
}

void set_title ( WMENU* menu, char* title )
{
	if ( title ) {	
		menu->title = set_title_iml(menu, title);
		return;
	}	

	menu->title = NULL;
}

static char* set_title_iml ( WMENU* menu, char* title )
{
	char*   tmp_title = NULL;
	uint8_t tmp_title_size = 0;

	tmp_title_size = strlen(title);
	if ( tmp_title_size > (menu->w / 2) ) 
		return false;

	tmp_title = (char*) malloc(sizeof(tmp_title_size));
	if ( !tmp_title )	
		return false;

	strcpy(tmp_title, title);	
	return tmp_title;
}

static void print_menu_iml ( WMENU* menu )
{
	uint8_t x, y, shift;
	
	x = y = 1;	
	
	//box(menu->win, 0, 0);
	
	wborder(menu->win, '|', '|', '-', '-', '*', '*', '*', '*');
	if ( menu->title ) {
		switch ( menu->title_pos ) {
			case L_POS:
				shift = 1;
				break;
			case M_POS:
				shift = ((menu->w - strlen(menu->title)) / 2);
				break;
			case R_POS:
				shift = (menu->w - strlen(menu->title)) - 1;
				break;
					
		}	
		mvwprintw(menu->win, y - 1, x + shift - 1 , "%s", menu->title);
	}	
		

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




