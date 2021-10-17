/*
Xenia Dela Cueva 
CS 50 21F Lab 4
Pagedir provides functions for writing files of webpage content 
Will be used by crawler and other parts of the TSE lab like indexer and querier
**/


/******** pagedir_init ************************/
/* Initializes the pageDirectory for file writing by crawler
 *
 * Caller provides:
 *   an existing page directory
 *
 * We return:
 *   true if we are able to open and close a file
 *   flase if we are unable to open the file
 */
bool pagedir_init(const char* pageDirectory);

/******** pagedir_save ************************/
/* Writes the contents of a webpage to the apporpriate file in a given directory
 *
 * Caller provides:
 *   an existing page directory
 *   a valid webpage
 *   a valid docID
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);