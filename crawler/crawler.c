/**
 * Xenia Dela Cueva
 * CS50 21F Lab 4
 * Crawler
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <hashtable.h>
#include <webpage.h>
#include <bag.h>
#include "mem.h" 
#include "pagedir.h"



/******** global variables ************/
char* seedURL;
char* pageDirectory;
int maxDepth;

/************* function prototypes ***************/
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);


int
main(int argc, char* argv[])
{

    //url is argv[1], page directory is argv[2], max depth is arg[3]
    int depth = 0;
    parseArgs(argc, argv, &argv[1], &argv[2], &depth);
    crawl(argv[1], argv[2], depth);
    exit(0);
}


static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{ 
    //url is argv[1], page directory is argv[2], max depth is arg[3]
    //making sure valid number of arguments
    if (argc != 4) {
        fprintf(stderr, "Invalid number of given arguments (must be 4 arguments)\n");
        exit(1);

    }
    else {
        
        if(seedURL != NULL && pageDirectory != NULL && argv[3] != NULL) {
            
            sscanf(argv[3], "%d", maxDepth); 
            
            //for maxDepth, ensure it is an integer in specified range
            if (*maxDepth < 0 || *maxDepth > 10) {
                fprintf(stderr, "maxDepth must be between 0 and 10; inputted maxDepth of %d is invalid\n", *maxDepth);
                exit(1);
                }

            //for URL making sure it is normalized and internal

            char* url_test = normalizeURL(argv[1]);

            if (url_test == NULL)  {
                fprintf(stderr, "Invalid URL given\n");
                exit(1); 
            }

            else {
                if (isInternalURL(url_test)) {
                    strcpy(*seedURL, argv[1]);
                }

                else {
                    mem_free(*seedURL);
                    fprintf(stderr, "Invalid URL given\n");
                    exit(1);
                }
            }

            //validating and parsing page directory
            if (pagedir_init(argv[2])) {
                strcpy(*pageDirectory, argv[2]);
            }

            else {
                fprintf(stderr, "Page directory failed to initialize\n");
                exit(1);
            //}
        }
    }
    
}


static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) 
{

    //initialize the hashtable and add the seedURL
    hashtable_t* hashtable_crawl;
    bag_t* bag_crawl;
    int hashtable_size = 200;
    char* hash_item = "";
    hashtable_crawl = hashtable_new(hashtable_size); 
    hashtable_insert(hashtable_crawl, seedURL, hash_item); 

    //initialize the bag and add a webpage representing the seedURL at depth 0
    webpage_t* first_page = webpage_new(seedURL, 0, NULL);
    bag_crawl = bag_new();
    bag_insert(bag_crawl, first_page); 
    
    int docID = 1;

    if (hashtable_crawl == NULL) {
        fprintf(stderr, "hashtable failed to initialize");
        exit(1);
    }
    if (bag_crawl == NULL) {
        fprintf(stderr, "bag failed to initialize");
        exit(1);
    }

    webpage_t* current;

    //while bag is not empty
    while (bag_crawl != NULL) {
        current = bag_extract(bag_crawl);

        //pull a webpage from the bag
        bag_extract(bag_crawl);

        //fetch the HTML for that webpage, if fetch was successful
        if (webpage_fetch(current)) {
            //save the webpage to pageDirectory
            pagedir_save(current, pageDirectory, docID); 
            docID ++;

            //if the webpage is not at maxDepth,
            if (webpage_getDepth(current) < maxDepth) { 
                //pageScan that HTML
                pageScan(current, bag_crawl, hashtable_crawl); 
                }
            
        }

        else {
            fprintf(stderr, "unable to fetch html\n");
            exit(1);
        }

        //delete that webpage
        webpage_delete(current);
    }
    //delete the hashtable and bag
    hashtable_delete(hashtable_crawl, NULL) ; 
    bag_delete(bag_crawl, webpage_delete); 

}




static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
    int position = 0;
    char* hash_item = "";

    char* next_URL = webpage_getNextURL(page, &position); 

    //while there is another URL in the page
    while (next_URL != NULL) {

        //if that URL is Internal,
        if (isInternalURL(next_URL)) {
            //insert the webpage into the hashtable 
            //if that succeeded,
            if (hashtable_insert(pagesSeen, next_URL, hash_item))  {
                webpage_t* new_page = webpage_new(next_URL, webpage_getDepth(page) + 1, NULL);  

                //insert the webpage into the bag
                bag_insert(pagesToCrawl, new_page);
            }

            //free the URL
            else {
               mem_free(next_URL);
            }

        }
        //free the URL
        mem_free(next_URL);

    }

}





