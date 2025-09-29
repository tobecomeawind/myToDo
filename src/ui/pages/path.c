#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "path.h"


static PATH* check_path_size ( PATH* ptp, const char* subpath );

PATH* init_path()
{
	PATH* ptp; // path pointer
	char* tmp_path;

	ptp = (PATH*) malloc(sizeof(PATH));
	if ( !ptp ) return NULL;
	
	tmp_path = (char*) malloc(sizeof(char) * PATH_DEFAULT_SIZE);	
	if ( !tmp_path ) return NULL;

	strcpy(tmp_path, DATA_PATH);
	ptp->path = tmp_path;
	ptp->max_size = PATH_DEFAULT_SIZE;	
	ptp->cur_size = strlen(DATA_PATH) + 1;

	return ptp;	
}

void del_path( PATH *ptp )
{
	if ( !ptp ) return;

	free(ptp->path);
	free(ptp);
}


void append_path( PATH* ptp, const char* subpath )
{
	ptp = check_path_size(ptp, subpath);
	if ( !ptp ) return;
	
	strcat(ptp->path, "/");	
	strcat(ptp->path, subpath);	
}


void go_back_path( PATH* ptp )
{
	// go_back_path(/home/me/test) -> return /home/me

	char* end = ptp->path + ptp->cur_size;

	while ( *end != '/' )
		end--;

	*end = '\0';
}


static PATH* check_path_size ( PATH* ptp, const char* subpath )
{
	uint16_t subpath_size = strlen(subpath);
	char*    tmp_path;	
	if ( ptp->cur_size + subpath_size > ptp->max_size ) {
		tmp_path = realloc(ptp->path, sizeof(ptp->max_size * 2));
		if ( !tmp_path ) return NULL;

		ptp->path = tmp_path;
		ptp->max_size *= 2;
	}	

	ptp->cur_size += subpath_size;
	return ptp;
}

