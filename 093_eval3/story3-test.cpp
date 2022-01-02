#include <iostream>

#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    printError("Error: invalid command line");
  }

  Story s;
  s.createStory(argv[1]);
  Story s2 = s;
  Story s3;
  s3 = s;

  return EXIT_SUCCESS;
}
