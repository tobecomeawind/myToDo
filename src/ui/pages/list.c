#include <dirent.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"


static void del_list (LIST* lp);
static LIST* init_list_iml ( void );
static void append_list ( LIST* lp, const char* filename );
static LIST* init_list ( const char* dirname );


LIST* read_dir_list ( const char* dirname )
{
	DIR*           dp;    // dir      pointer
	struct dirent* ditem; // dir item pointer
	const  char*   subdirname;	
	LIST*          lp;   // dir list pointer	

	dp = opendir(dirname);
	if ( !dp ) return NULL;

	lp = init_list_iml();
	if ( !lp ) return NULL;


	while ( (ditem = readdir(dp)) != NULL ) {
		subdirname = ditem->d_name;
		if ( strcmp(ditem->d_name, ".") == 0 )
			subdirname = NULL;	
		else if ( strcmp(ditem->d_name, ".." ) == 0 )
			subdirname = "Back";	
		
		append_list(lp, subdirname);
	}


	closedir(dp);

	return lp;	
}



static void append_list ( LIST* lp, const char* filename )
{					
	if ( !filename ) return;	
	insert_list(lp, lp->size - 1, filename);
}


void insert_list ( LIST* lp, uint8_t index, const char* filename )
{
	if ( index > lp->size ) return;

	char** tmp_list;	
	char*  tmp_item;
	char*  prev_item = NULL;
	
	char*  tmp_filename;

	tmp_list = (char**) realloc(lp->list, sizeof(char*) * lp->size);
	if ( !tmp_list ) return;
	lp->list = tmp_list; 		

	// shift to right, with shifting every element
	// use tmp_item, and prev_item
	for ( int i = index; i < lp->size; i++ ) {
		tmp_item = lp->list[i];
	   	lp->list[i] = prev_item;
		prev_item = tmp_item;	
	}	

	tmp_filename = (char*) malloc(sizeof(strlen(filename)));
	if ( !tmp_filename ) return;

	strcpy(tmp_filename, filename);	 //copy filename to list
	
	lp->list[index] = tmp_filename;

	++lp->size;
}





static LIST* init_list_iml ( void )
{
	// Init list		
	
	LIST* lp;
	char** list;

	lp = (LIST*) malloc(sizeof(LIST));
	if ( !lp ) return NULL;

	list = (char**) malloc(sizeof(char*));
	if ( !list ) return NULL;

	lp->list = list;
	lp->size = 1;

	return lp;
}


static void del_list (LIST* lp)
{
	// Delete dir list	
	
	if ( !lp ) return;

	for ( int i = 0; i < lp->size; i++ ) 
		free(lp->list[i]);	
	
	free(lp->list);

	free(lp);		
}

