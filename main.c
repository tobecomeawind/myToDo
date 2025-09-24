#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

static WINDOW* create_newwin ( int h, int w, int y, int x );
static void destroy_win ( WINDOW* local_win );

int main ( int argc, char* argv[] ) 
{
	WINDOW* my_win;
	int startx, starty, width, height;

	int ch;

	initscr();
	cbreak();

	keypad(stdscr, TRUE);

	height = 3;
	width  = 10;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(height, width, starty, startx);

	while ( (ch = getch()) != KEY_F(1) ) {
		switch ( ch ) {
			case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty, --startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty, ++startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(height, width, ++starty, startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(height, width, --starty, startx);
				break;
		}	
	}

	endwin();
	return 0;
}

static WINDOW* create_newwin ( int h, int w, int y, int x ) 
{
	WINDOW* local_win;
	
	local_win = newwin(h, w, y, x); // 

	box(local_win, 0, 0); // 0, 0 default for vertical and horizontal lines
	wrefresh(local_win);

	return local_win;
}

static void destroy_win ( WINDOW* local_win )
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	// window ptr
	// char left side
	// char right side
	// char top side
	// char bottom side
	// char top left corner
	// char top right corner
	// char bottom left cornen
	// char bottom right corner
	
	wrefresh(local_win);
	delwin(local_win);
}




