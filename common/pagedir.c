/**
 * Xenia Dela Cueva
 * CS50 21F Lab 4
 * Pagedir
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"
#include "pagedir.h"
#include "mem.h"


/************* function prototypes ***************/
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/******** pagedir_init ************************/
/* refer to pagedir.h for function overview **/
bool pagedir_init(const char* pageDirectory) 
{

    FILE* fp;
    char* file_path = mem_malloc(strlen(pageDirectory) + 10);


     //construct the pathname for the .crawler file in that directory
     strcpy(file_path, pageDirectory);

     //to append part of the string
     strcat(file_path, "/.crawler");

    //open the file for writing; on error, return false.
    if ((fp = fopen(file_path, "w")) == NULL) { //"w" is to write
        return false;
    }

    //close the file and return true.
    fclose(fp);
    mem_free(file_path);
    return true;

}



/******** pagedir_save ************************/
/* refer to pagedir.h for function overview **/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
    FILE* fp;
    char* file = malloc(strlen(pageDirectory));
    char* path = mem_malloc(strlen(pageDirectory) + 10);

    //docID to string format to name files
    sprintf(file, "%d", docID);
    

    //construct the pathname for the page file in pageDirectory
    strcpy(path, pageDirectory);
    strcat(path, "/");
    strcat(path, file);

    //open that file for writing
    if ((fp = fopen(path, "w")) != NULL) {
        //print the URL
        char* url = webpage_getURL(page);
        fprintf(fp, "%s\n", url);

        //print the depth
        int depth = webpage_getDepth(page);
        fprintf(fp,"%d\n", depth);

        //print the contents of the webpage
        fprintf(fp,"%s\n",webpage_getHTML(page));
        fclose(fp);
        mem_free(path);
    }

    else {
        fprintf(stderr, "Null file");
        mem_free(path);
        exit(1);
    }
}



