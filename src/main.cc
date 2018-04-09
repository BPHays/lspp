// Copyright (c) 2018 Brian Hays
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <experimental/filesystem>
#include <iostream>
#include <optional>

#include "format.hh"
#include "formattedPath.hh"

namespace fs = std::experimental::filesystem;

int main(int argc, char ** argv) {
  (void) argc;
  (void) argv;
  for (auto const & ent : fs::directory_iterator(argv[1])) {
    auto p = fs::path(ent);
    auto fmt = lspp::Format::get_format(p);
    auto name = p.filename();
    lspp::FormattedPath fp(name, fmt);
    std::cout << fp << "\n";
  }
  return 0;
}
