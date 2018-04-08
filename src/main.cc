
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int argc, char ** argv) {
  (void) argc;
  (void) argv;
  for (auto const & ent : fs::directory_iterator(".")) {
    std::cout << ent << "\n";
  }
}
