#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

bool sortFunc(std::string & s1, std::string & s2) {
  return s1 < s2;
}

void sortFile(std::istream & f) {
  std::string str;
  std::vector<std::string> data;
  while (std::getline(f, str)) {
    data.push_back(str);
  }

  sort(data.begin(), data.end(), sortFunc);
  std::vector<std::string>::iterator it = data.begin();
  for (it = data.begin(); it != data.end(); it++) {
    std::cout << *it << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    // input from std in
    sortFile(std::cin);
  }

  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream f;
      f.open(argv[i], std::ifstream::in);
      if (!f.is_open()) {
        std::cerr << argv[i] << "is not exist" << std::endl;
        return EXIT_FAILURE;
      }
      sortFile(f);
      f.close();
    }
  }

  return EXIT_SUCCESS;
}
