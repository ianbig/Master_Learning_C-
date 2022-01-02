#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

/*** step 1 ****/
/* 
- usage: parse file and replace category name specified by _[your category name]_
- parameter
  @filename: file to parsed
  @cats: catarray_t array data structure
  @n_opt: indicate n option
- return:
  return buffer with parsed file, exit with EXIT_FAULURE if unexpected error occur
*/
char * parseFile(const char * fileNamae, catarray_t * cats, int n_opt);
/* 
- usage: parsed single line as input and exchange blank word with corresponding word if there is wrong format of blank word, it would exit failure
- parameter
  @parsed: buffer to store parsed line
  @mvptr: current parsing line
  @sz: size of parsed buffer
- return:
  return line with replaced words according to the category. if there is format error, exit program with EXIT_FAILURE
*/
char * parseLine(char ** parsed,
                 char * mvptr,
                 size_t * sz,
                 catarray_t * cats,
                 category_t * track,
                 int n_opt);

/**** step 2 *****/
// usage: initiate catarray_t data structure
void init_cats(catarray_t * cats);
// usage: split the lineptr by ':', and put the words before ':' to key, and the other to words
void divideKeyWords(char * lineptr, char ** key, char ** words);
// usage: find category in catarray_t, and return the address of that category in catarray_t
category_t * findCat(char * key, catarray_t * cats);
// usage: add key to catarray_t to add new category, and return the address of newly added category
category_t * addNewCat(catarray_t * cats, const char * key);
// usage: add words to the category specified by cat
void addWordToCat(category_t * cat, const char * words);
// usage: parse the conent in filename, and return a corresponding catarray_t*
catarray_t * parseCats(const char * filename, int debug);
// usage: free the data structure of catarray_t*
void freeCats(catarray_t * cats);
// testing function
void printAddNewCats(catarray_t * cats);
/**** step 3 *****/
// usage: initialize tracking for tracking used words
void init_track(category_t * track);
// usage: pick the reference words from tracking
char * pickWRef(const char * cat, category_t * track);
// usage: add words to tracking
void addTrack(category_t * track, const char * words);
// usage: free the tracking
void freeTrack(category_t * track);

// testing function
void printTrack(category_t * track);

/**** step 4 ******/
// usage: delete words in cat
void deleteWords(category_t * cat, const char * words);

// testing function

#endif
