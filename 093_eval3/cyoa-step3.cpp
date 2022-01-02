#include <iostream>

#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    printError("Error: invalid command line");
  }

  Story s;
  s.createStory(argv[1]);
  std::vector<int> depth = s.calcDepth();
  s.printDepth(depth);

  return EXIT_SUCCESS;
}
