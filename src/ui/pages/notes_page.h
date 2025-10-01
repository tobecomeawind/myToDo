#ifndef notes_page_H
#define notes_page_H

#define COUNT_MENUS 4

#define DIR_TYPE_TO_CHAR_M(dir_type, title) \
	switch(dir_type) {\
		case(YEARS): \
			title = "Years"; \
			break; \
		case(MONTHS): \
			title = "Months"; \
			break; \
		case(WEEKS): \
			title = "Weeks"; \
			break; \
		case(DAYS): \
			title = "Days"; \
			break; \
	} \

typedef enum menu_types_enum {  // /data
	YEARS = 0,     // /2025
	MONTHS,        // /9
	WEEKS,         // /3
	DAYS           // /28
} MENU_TYPES;

void init_notes_page();
void del_notes_page();

#endif
