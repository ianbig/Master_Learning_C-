#ifndef _STORY_HPP_
#define _STORY_HPP_

#include <dirent.h>
#include <sys/types.h>

#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "graph.hpp"
#include "page.hpp"
#include "utility.hpp"

class Story {
  typedef struct pageCheck_t {
    int pageNum;
    std::string fname;
  } pageCheck;

  typedef struct depth_calc_t {
    int depth;
    int pageNum;
  } depth_calc_t;

  class StoryComp {
   public:
    bool operator()(pageCheck s1, pageCheck s2) { return s1.pageNum < s2.pageNum; }
  };

  std::vector<Page> storyVec;  // page1.txt start w/ index 0 (TODO: refactor this)
  int story_len;
  Graph * ref;
  std::vector<std::vector<page_choice> > wp;

  // build the adjacency matrix for story
  // check the format of each file in story
  // check wheter it is an valid story
  void groupPages(std::vector<pageCheck> & check, std::string dir);
  // check wheter the reference is in the story
  // build up the reference graph table
  void buildRef(Page & p);
  // do the following check for the story
  // a. every page is referenced by at least one page
  // b. the reference page must exist
  // c. at least one win and lose page
  bool validateStory();
  // validate whether the specific pafgNum is following the reference rules
  // if follos return true; otherwise, return 0
  bool validatePageRef(int pageNum);

  // testing function
  void printStory();
  // if the input is invalid, return -1
  int checkChoose(Page & page, std::string input);
  void dfs_find_w(page_choice cur,
                  std::vector<bool> visited,
                  std::vector<page_choice> wp,
                  int option);

 public:
  // ========= follow the rule of three ============
  Story() : story_len(0), ref(NULL) {}
  ~Story();
  Story & operator=(const Story & rhs);
  Story(const Story & rhs);
  // =======================
  // create the story in directory and create the graph adjacent matrix
  // input: directory to build story
  void createStory(const char * dir);
  // prompt the user to choose option for their story
  void readStory();
  // calculate the depth in story from page 1 in every other page in story
  std::vector<int>
  calcDepth();  // TODO (if wanna): refactor code to make depth vector become private member
  void printDepth(std::vector<int> & depth);
  // find the path to win, it would avoid cycle
  void findWinPath();
  // print every win path
  void printWinPath();
};
#endif
