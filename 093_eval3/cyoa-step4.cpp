#include <iostream>
#include <vector>

#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    printError("Error: invalid command line");
  }

  Story s;
  s.createStory(argv[1]);
  s.findWinPath();
  s.printWinPath();

  return EXIT_SUCCESS;
}
