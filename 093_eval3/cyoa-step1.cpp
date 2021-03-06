#include "page.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Error command line" << std::endl;
    return EXIT_FAILURE;
  }

  Page page;
  page.parseFile(argv[1]);
  page.print();

  return EXIT_SUCCESS;
}
