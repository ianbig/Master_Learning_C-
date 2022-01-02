#include "story.hpp"

Story::~Story() {
  delete ref;
}

Story::Story(const Story & rhs) :
    storyVec(rhs.storyVec),
    story_len(rhs.story_len),
    wp(rhs.wp) {
  ref = new Graph();
  *ref = *(rhs.ref);
  // for testing
  /*
  std::cout << "======= graph for rhs (test copy) =======" << std::endl;
  rhs.ref->printGraph();
  std::cout << "======= graph for this (test copy)=======" << std::endl;
  ref->printGraph();
  */
}

Story & Story::operator=(const Story & rhs) {
  if (this != &rhs) {
    storyVec = rhs.storyVec;
    story_len = rhs.story_len;
    wp = wp;
    ref = new Graph();
    *ref = *(rhs.ref);
    // for testing
    /*
    std::cout << "======= graph for rhs (test assignment) =======" << std::endl;
    rhs.ref->printGraph();
    std::cout << "======= graph for this (test assignment)  =======" << std::endl;
    ref->printGraph();
    */
  }

  return *this;
}

void Story::createStory(const char * dir) {
  DIR * dirp = opendir(dir);
  if (dirp == NULL) {
    printError("Error: invalid directory");
  }

  errno = 0;
  struct dirent * fp;
  std::vector<pageCheck> check;
  while ((fp = readdir(dirp)) != NULL) {
    // eascape . and ..
    std::string fname(fp->d_name);
    if (fname.compare(".") == 0 || fname.compare("..") == 0) {
      continue;
    }

    int page_num = extractFileNum(fname);
    if (page_num == -1) {
      continue;
    }
    // push the struct to pageCheck vector
    pageCheck pc;
    pc.pageNum = page_num;
    pc.fname = fname;
    check.push_back(pc);
  }

  if (errno != 0) {
    printError("Error: unexpected behavior when reading directory");
  }

  // group story out
  groupPages(check, dir);
  // ref->printGraph();

  int ret = closedir(dirp);
  if (ret == -1) {
    printError("Unexpec hapen when closing directory");
  }
}

void Story::groupPages(std::vector<pageCheck> & check, std::string dir) {
  if (check.size() < 3) {
    printError("Error: there must be page1.txt, Win page and Lose page");
  }

  sort(check.begin(), check.end(), StoryComp());
  if (check[0].pageNum != 1) {
    printError("Erorr: story should start at page1.txt");
  }

  // get the number of pages in the story
  int expect_page = 1;
  for (size_t i = 0; i < check.size(); i++) {
    if (check[i].pageNum != expect_page) {
      break;
    }
    expect_page++;
  }

  story_len = expect_page - 1;
  ref = new Graph(story_len);
  for (int i = 0; i < story_len; i++) {
    Page p;
    std::string fname = dir + "/" + check[i].fname;
    p.parseFile(fname);
    buildRef(p);
    storyVec.push_back(p);
  }

  validateStory();
}

void Story::printStory() {
  for (size_t i = 0; i < storyVec.size(); i++) {
    // storyVec[i].print();
    std::cout << storyVec[i].getPageNum() << std::endl;
  }

  ref->printGraph();
}

void Story::buildRef(Page & p) {
  std::vector<Option> & refs = p.getChoices();
  for (size_t i = 0; i < refs.size(); i++) {
    try {
      ref->addEdge(refs[i].getPageNum(), p.getPageNum());
    }

    catch (std::out_of_range & e) {
      printError("buildRef: page point to non-exist story");
    }
  }
}

// check wheter the each page is reference by at least one page, and there must be at least one win page and one lose page
bool Story::validateStory() {
  // validate at least reference by one other page choices
  bool win = false, lose = false;
  for (size_t i = 1; i < storyVec.size(); i++) {  // skip page1.txt
    if (validatePageRef(storyVec[i].getPageNum()) == false) {
      printError(
          "validateStory: there are pages that do not get referenced");  // TODO : delete this when finalized
      return false;
    }

    if (storyVec[i].getres() == WIN) {
      win = true;
    }

    else if (storyVec[i].getres() == LOSE) {
      lose = true;
    }
  }

  if (lose == true && win == true) {
    return true;  // meaning
  }

  printError(
      "missing at least one win page or lose page");  // TODO: delete this when finalized
  return false;
}

bool Story::validatePageRef(int pageNum) {
  for (int i = 1; i <= story_len; i++) {
    if (ref->isAdjacent(pageNum, i) == true) {
      return true;
    }
  }

  return false;
}

int Story::checkChoose(Page & page, std::string input) {
  // check whether choice is unsigned
  unsigned pick = 0;
  std::stringstream ss(input);
  ss >> pick;
  if (ss.fail() == true) {
    return -1;
  }
  // check whether the choice corresponding given choice
  std::vector<Option> choices = page.getChoices();
  if (pick <= choices.size() && pick > 0) {
    return choices[pick - 1].getPageNum();
  }

  return -1;
}

void Story::readStory() {
  Page & page = storyVec[0];
  page.print();

  std::string input;
  while (std::getline(std::cin, input)) {
    // check whether input is valid number (unsigned)
    // check wehter the option is correct (no choosing page not suppose to choose e.g. choosing option that do not provided)
    int ci = -1;
    if ((ci = checkChoose(page, input)) == -1) {
      std::cerr << "That is not a valid choice, please try again" << std::endl;
      continue;
    }
    // go to corresponding choice, and output the content
    page = storyVec[ci - 1];  // because index start from 0
    page.print();
    // if it is a WIN or LOSE page exit break the loop
    if (page.getres() == WIN || page.getres() == LOSE) {
      break;
    }
  }
}

std::vector<int> Story::calcDepth() {
  std::vector<int> depth(story_len + 1,
                         -1);  // we accomdate for page number, making index 0 dummy node
  std::vector<bool> visited(story_len + 1, false);

  depth_calc_t depthTmp;
  depthTmp.depth = 0;
  depthTmp.pageNum = 1;
  visited[1] = true;
  std::queue<depth_calc_t> cont;
  cont.push(depthTmp);

  while (!cont.empty()) {
    depthTmp = cont.front();
    depth[depthTmp.pageNum] = depthTmp.depth;
    cont.pop();

    // loop throgh all the neighbor
    for (int i = 1; i <= story_len; i++) {
      if (ref->isAdjacent(i, depthTmp.pageNum) && visited[i] == false) {
        depth_calc_t tmp;
        tmp.depth = depthTmp.depth + 1;
        tmp.pageNum = i;
        visited[tmp.pageNum] = true;
        cont.push(tmp);
      }
    }
  }

  return depth;
}

void Story::printDepth(std::vector<int> & depth) {
  for (size_t i = 1; i < depth.size(); i++) {
    if (depth[i] == -1) {
      std::cout << "Page " << i << " is not reachable" << std::endl;
    }

    else {
      std::cout << "Page " << i << ":" << depth[i] << std::endl;
    }
  }
}

void Story::findWinPath() {
  std::vector<bool> visited(story_len + 1, false);
  std::vector<page_choice> fp;
  page_choice first;

  first.pageNum = 1;
  std::vector<page_choice> opts = storyVec[first.pageNum - 1].getOpts();
  for (size_t i = 0; i < opts.size(); i++) {
    first.opt = i + 1;
    dfs_find_w(first, visited, fp, opts[i].pageNum);
  }
}

void Story::dfs_find_w(page_choice cur,
                       std::vector<bool> visited,
                       std::vector<page_choice> fp,
                       int option) {
  fp.push_back(cur);
  visited[cur.pageNum] = true;

  if (storyVec[option - 1].getres() == WIN) {
    // save path
    page_choice nxt;
    nxt.pageNum = option;
    nxt.opt = 0;
    fp.push_back(nxt);
    wp.push_back(fp);
  }

  else if (storyVec[option - 1].getres() == LOSE) {
    return;
  }

  else {
    std::vector<page_choice> opts = storyVec[option - 1].getOpts();
    page_choice nxt;
    nxt.pageNum = option;
    for (size_t i = 0; i < opts.size(); i++) {
      if (visited[nxt.pageNum] == true) {
        continue;
      }
      nxt.opt = i + 1;
      dfs_find_w(nxt, visited, fp, opts[i].pageNum);
    }
  }
}

void Story::printWinPath() {
  if (wp.empty()) {
    std::cout << "This story is unwinnable!" << std::endl;
  }

  for (size_t i = 0; i < wp.size(); i++) {
    for (size_t j = 0; j < wp[i].size() - 1; j++) {
      std::cout << wp[i][j].pageNum << "(" << wp[i][j].opt << ")"
                << ",";
    }

    std::cout << wp[i][wp[i].size() - 1].pageNum << "("
              << "win"
              << ")";

    std::cout << std::endl;
  }
}
