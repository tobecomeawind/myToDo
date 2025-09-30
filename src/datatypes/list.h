#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include "list.h"

typedef struct list_struct {
	char**  list;
	uint8_t size;
} LIST;

LIST* init_from_dir_list ( const char* dirname );
LIST* init_from_arr_list ( char* arr[], uint8_t size );
void insert_list ( LIST* lp, uint8_t index, const char* filename );
void del_list (LIST* lp);

#endif
