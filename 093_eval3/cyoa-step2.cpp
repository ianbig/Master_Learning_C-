#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    printError("Error: commnad line invalid");
  }

  Story s;
  s.createStory(argv[1]);
  s.readStory();

  return EXIT_SUCCESS;
}
