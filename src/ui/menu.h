#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <stdint.h>

typedef struct menu_window_struct {
	WINDOW* win;
	char**  choices;
	uint8_t n_choices;
	uint8_t current;	
} WMENU;



uint8_t choice_menu ( WMENU* menu );
WMENU* init_menu ( uint8_t height,  uint8_t weight,
                   uint8_t starty,  uint8_t startx,
                   char**  choices, uint8_t n_choices);
void del_menu ( WMENU* menu );

	
#endif
