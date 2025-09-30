#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <stdint.h>
#include "list.h"

typedef struct menu_window_struct {
	WINDOW* win;
	LIST* 	choices;
	uint8_t current;	
} WMENU;


void set_list_menu ( WMENU* menu, LIST* list);

uint8_t choice_menu ( WMENU* menu );
WMENU* init_menu ( uint8_t height,  uint8_t weight,
                   uint8_t starty,  uint8_t startx,
                   LIST* lp);
void del_menu ( WMENU* menu );

	
#endif
