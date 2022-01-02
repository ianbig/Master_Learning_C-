#ifndef _PAGE_H
#define _PAGE_H
#include <climits>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "option.hpp"
#include "utility.hpp"

enum result_t { NONE = 0, WIN, LOSE };

class Page {
  std::vector<Option> choices;
  std::string story;
  result_t result;
  int pageNum;

  std::string getOpt(std::string tmpLine, std::string cat);

 public:
  Page() : result(NONE), pageNum(0) {}
  // parse the filename indicated, store essential info in specified filename
  // option in page
  // story in page
  // its result (NONE, WIN, LOSE) : NONE means is an option page
  // the pageNum of this page
  // if error happen exit current process with EXIT_FAULURE
  void parseFile(std::string filename);
  std::vector<Option> & getChoices() { return choices; }
  // print out the Page Story, prompt, and result page
  void print();
  result_t getres() { return result; }
  int getPageNum() { return pageNum; }
  std::vector<page_choice> getOpts();
};
#endif
