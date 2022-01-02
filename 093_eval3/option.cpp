#include "option.hpp"

Option::Option(std::string num_t, std::string text_t) : pageNum(0), text(text_t) {
  // test whether num_t is a valid number
  std::stringstream ss;
  ss << num_t;
  ss >> pageNum;
  if (ss.fail()) {
    printError("invalid numner for option");
  }
}

int Option::getPageNum() {
  return pageNum;
}

std::string Option::getText() {
  return text;
}
