#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <stdint.h>
#include "list.h"

typedef enum wmenu_title_position_enum {
	L_POS = 0,
	M_POS,	
	R_POS,
} TITLE_POS;

typedef struct menu_window_struct {
	WINDOW*   win;

	uint8_t   h, w, y, x;

	char*     title;
	TITLE_POS title_pos;	

	LIST* 	  choices;
	uint8_t   current;	
} WMENU;


void set_list_menu ( WMENU* menu, LIST* list);
void set_title ( WMENU* menu, char* title );

uint8_t choice_menu ( WMENU* menu );
WMENU* init_menu ( uint8_t height,  uint8_t   weight,
                   uint8_t starty,  uint8_t   startx,
				   char*   title,   TITLE_POS title_pos,
                   LIST* lp);
void del_menu ( WMENU* menu );

	
#endif
