#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>

#include "menu.h"
#include "list.h"
#include "main_page.h"
#include "notes_page.h"
#include "page_changer.h"

void init_main_page()
{
	WMENU* menu;
	LIST*  choices_list;	
	uint8_t user_choice, w, h; 

	h = 10;
	w = 20;
		
	char* list[] = {"Notes", "Goals and Tasks", "Progress", "Quit"};

	choices_list = init_from_arr_list(list, sizeof(list) / sizeof(char*));

	menu = init_menu(h,               w,
			        (LINES - h) / 2, (COLS - w) / 2,
				    "Main",      L_POS,	
					choices_list);

	if ( !menu ) {
		printf("Menu not created !!!");
		return; 	
	}

	while ( 1 ) {
		user_choice = choice_menu(menu);
		switch ( user_choice ) {
			case 0:
				change_page(&delete_main_page, &init_notes_page);
				break;
			case 1:
			case 2:
				break;
			case 3:
				return;	
		}	
	}

}

void delete_main_page()
{

}
