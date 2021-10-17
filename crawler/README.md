# CS50 TSE LAB 4
## Xenia Dela Cueva (xdelacuev1)

it must always have three arguments.

### crawler

The TSE crawler is a standalone program that crawls the web and retrieves webpages starting from a "seed" URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given "depth". To work properly, it must always have 4 arguments (aside from calling the function, the URL, the page directory to keep the webpages, and the depth of crawling).

### Usage

The crawler is implemented in `crawler.c`, and uses the following functions:

```c
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
```


### Implementation

Crawler uses a hashtable (which acts as a record of URLs seen) and a bag (which acts as a record of URLs already visited) to keep track of what it has crawled through and what it hasn't yet.
It uses webpage.h for different functions that handles the html of a webpage or validates the URL.

The `crawl` method searches the URLs and saves its webpages to the given pageDirectory within the maximum depth

The `parseArgs` method parses through the given arguments and validates them (like the URL) in order for crawler to begin going
through the webpages.

The `pageScan` method validates a given URL and adds it to the hashtable and its webpage to the bag.

### Assumptions

No assumptions beyond those that are clear from the spec.

We assume that the items in the hashtable are not of any significance as the URLs are the keys (which is what we need).
webpage_fetch enforces the 1-second delay for each fetch, so crawler doesn't implement that part of the spec.

We also assume that the bag is unordered and that pageDirectory does not contain any files named an integer prior to calling the function

### Files

* `Makefile` - compilation procedure
* `crawler.c` - the implementation
* `testing.sh` - testing script

### Compilation

To compile, simply `make`.

## Testing
A testing script is used to run crawler and its different scenarios
