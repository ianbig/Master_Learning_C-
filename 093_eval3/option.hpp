#ifndef _OPTION_HPP_
#define _OPTION_HPP_
#include <iostream>
#include <sstream>

#include "utility.hpp"

class Option {
  int pageNum;
  std::string text;

 public:
  Option(std::string num_t, std::string text_t);
  int getPageNum();
  std::string getText();
};

#endif
