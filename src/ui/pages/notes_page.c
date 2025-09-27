#include <dirent.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "menu.h"


typedef struct dir_list_struct {
	char**  list;
	uint8_t size;
} DLIST;


static void del_dir_list (DLIST* dlp);
static DLIST* init_dir_list_iml ( void );
static void append_dir_list ( DLIST* dlp, const char* filename );
static DLIST* init_dir_list ( const char* dirname );




static DLIST* init_dir_list ( const char* dirname )
{
	DIR*           dp;    // dir      pointer
	struct dirent* ditem; // dir item pointer
	DLIST*         dlp;   // dir list pointer	

	dp = opendir(dirname);
	if ( !dp ) return NULL;

	dlp = init_dir_list_iml();
	if ( !dlp ) return NULL;


	while ( (ditem = readdir(dp)) != NULL )
		append_dir_list(dlp, ditem->d_name);


	closedir(dp);

	return dlp;	
}



static void append_dir_list ( DLIST* dlp, const char* filename )
{		
	char** tmp_list;	
	char*  tmp_filename;
	
	if ( dlp->size != 1 ) { // we already init list,dont need realloc
		tmp_list = (char**) realloc(dlp->list, sizeof(char*) * dlp->size);
		if ( !tmp_list ) return; // check if memory error
		dlp->list = tmp_list;
	}
	
	tmp_filename = (char*) malloc(sizeof(strlen(filename)));
	if ( !tmp_filename ) return;

	strcpy(tmp_filename, filename);	 //copy filename to list
	
	dlp->list[dlp->size - 1] = tmp_filename;
	++dlp->size; //increase size
}


static DLIST* init_dir_list_iml ( void )
{
	// Init dir list		
	
	DLIST* dlp;
	char** list;

	dlp = (DLIST*) malloc(sizeof(DLIST));
	if ( !dlp ) return NULL;

	list = (char**) malloc(sizeof(char*));
	if ( !list ) return NULL;

	dlp->list = list;
	dlp->size = 1;

	return dlp;
}


static void del_dir_list (DLIST* dlp)
{
	// Delete dir list	
	
	if ( !dlp ) return;

	for ( int i = 0; i < dlp->size; i++ ) 
		free(dlp->list[i]);	
	
	free(dlp->list);

	free(dlp);		
}

