#include "page.hpp"

std::string Page::getOpt(std::string tmpLine, std::string cat) {
  if (tmpLine.compare("WIN") == 0) {
    result = WIN;
    return "res";
  }

  if (tmpLine.compare("LOSE") == 0) {
    result = LOSE;
    return "res";
  }

  if (tmpLine[0] == '#') {
    return "#";
  }

  size_t index = tmpLine.find(':');
  if (index == std::string::npos) {
    printError("missing ':' in parsing options");
  }

  std::string ret;
  if (cat == "num") {
    ret = tmpLine.substr(0, index);
  }

  else if (cat == "text") {
    ret = tmpLine.substr(index + 1);
  }

  return ret;
}

void Page::parseFile(std::string filename) {
  // validate fileName
  pageNum = extractFileNum(filename);
  if (pageNum == -1) {
    printError("Error: invalid filename!");
  }

  std::fstream fs(filename.c_str(), std::fstream::in);
  if (fs.is_open() == false) {
    printError("Error: file not open");
  }
  // get the navigation part unitl hit # (check for num, must be positive number)
  std::string tmpLine;
  while (std::getline(fs, tmpLine)) {
    std::string num = getOpt(tmpLine, "num");
    if (num.compare("#") == 0) {  // mean encounter #
      break;
    }

    if (result == NONE) {
      std::string choiceText = getOpt(tmpLine, "text");
      Option choice(num, choiceText);
      choices.push_back(choice);
    }
  }

  if (fs.eof()) {
    printError("Error: wrong story format in paseFile no #");
  }
  // get the story text
  while (std::getline(fs, tmpLine)) {
    story += tmpLine + "\n";
  }
  fs.close();
}

void Page::print() {
  std::cout << story << std::endl;

  size_t options = 1;
  if (result == NONE) {
    std::cout << "What would you like to do?" << std::endl << std::endl;
    for (std::vector<Option>::iterator it = choices.begin(); it != choices.end(); it++) {
      std::cout << " " << options << ". " << (*it).getText() << std::endl;
      options++;
    }
  }

  else if (result == WIN) {
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }

  else if (result == LOSE) {
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}

/*
Page::Page(const Page & rhs) {
  try {
    choices = rhs.choices;
    story = rhs.story;
    result = rhs.result;
    pageNum = rhs.pageNum;
  }

  catch (std::exception) {
    printError("Unexpected Behavior in Page Copy Constructor");
  }
}
*/
std::vector<page_choice> Page::getOpts() {
  std::vector<page_choice> ret;
  for (size_t i = 0; i < choices.size(); i++) {
    page_choice tmp;
    tmp.opt = i + 1;
    tmp.pageNum = choices[i].getPageNum();
    ret.push_back(tmp);
  }

  return ret;
}
