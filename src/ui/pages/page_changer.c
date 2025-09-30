#include <ncurses.h>


void change_page(void (*delete_old_page) (void), void (*init_new_page) (void))
{
	clear();	
	refresh();	
	
	if ( delete_old_page )
		(*delete_old_page)();
	if ( init_new_page )
		(*init_new_page)();	
}
