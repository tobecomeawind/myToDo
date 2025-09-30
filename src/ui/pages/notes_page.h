#ifndef notes_page_H
#define notes_page_H

#define COUNT_MENUS 4

typedef enum menu_types_enum {  // /data
	YEARS = 0,     // /2025
	MONTHS,        // /9
	WEEKS,         // /3
	DAYS           // /28
} MENU_TYPES;

void init_notes_page();

#endif
