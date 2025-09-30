#ifndef PATH_H
#define PATH_H

#define DATA_PATH "/home/tobecomeawind/pain/what_is_it/data"
#define PATH_DEFAULT_SIZE 128

typedef struct path_struct {
	char*   path;
	uint16_t cur_size;
	uint16_t max_size; 
} PATH;

PATH* init_path();
void del_path( PATH *ptp );
void append_path( PATH* ptp, const char* subpath );
void go_back_path( PATH* ptp );


#endif
