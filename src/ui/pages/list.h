#ifndef LIST_H
#define LIST_H

#include <stdint.h>

typedef struct list_struct {
	char**  list;
	uint8_t size;
} LIST;

LIST* read_dir_list ( const char* dirname );
void insert_list ( LIST* lp, uint8_t index, const char* filename );

#endif
