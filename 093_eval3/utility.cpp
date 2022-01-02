#include "utility.hpp"

int extractFileNum(std::string filename) {
  size_t p_pos = filename.find("page");
  if (p_pos == std::string::npos) {
    return -1;
    // printError("Error: expect pageX.txt");
  }
  size_t dot_pos = filename.find(".", p_pos);  // start find . after "page"
  if (dot_pos == std::string::npos) {
    return -1;
    // printError("Error: expect pageX.txt but missing .");
  }

  size_t num_start = p_pos + 4, num_len = dot_pos - num_start;
  std::stringstream s(filename.substr(p_pos + 4, num_len));
  int page_num = -1;
  s >> page_num;
  if (s.fail() || page_num < 1) {
    return -1;
    // printError("Error: expect pageX.txt but page number has issue");
  }

  size_t ext_pos = dot_pos + 1;
  if (filename.substr(ext_pos).compare("txt") != 0) {
    return -1;
    // printError("Error: expect pageX.txt but file extension has issue");
  }

  return page_num;
}

void printError(const char * msg) {
  std::cerr << msg << std::endl;
  exit(EXIT_FAILURE);
}
