#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <cstdlib>
#include <iostream>
#include <sstream>

typedef struct page_choice_t {
  int opt;
  int pageNum;
} page_choice;

// print the error based on message, and exit the process with EXIT_FAILURE
void printError(const char * msg);
// if the file do not have the filename format of pageX.txt, it would return -1
int extractFileNum(std::string filename);

#endif
