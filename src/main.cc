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
#include <optional>
#include <algorithm>
#include <iostream>

#include "format.hh"
#include "formattedPath.hh"
#include "longListing.hh"
#include "padding.hh"

namespace fs = std::experimental::filesystem;

int main(int argc, char ** argv) {
  (void) argc;
  (void) argv;

  // retreive
  std::vector<fs::path> paths;
  for (auto const & ent : fs::directory_iterator(argv[1])) {
    paths.emplace_back(ent);
  }

  // sort
  std::sort(paths.begin(), paths.end(), [](auto p1, auto p2) {
    return p1.string() < p2.string();
  });

  // pad
  lspp::Padding pad;
  for (auto const & p : paths) {
    auto name = p.filename();
    lspp::LongListing ll(p);
    pad.update_hard_links_max(
        std::to_string(ll.get_hard_link_count()).length());
    pad.update_owner_max(ll.get_owner().length());
    pad.update_group_max(ll.get_group().length());
    pad.update_size_max(std::to_string(ll.get_file_size()).length());
    pad.update_file_name_max(ll.get_path().filename().string().length());
  }
  std::cout << pad.size << "\n";

  // print
  for (auto const & p : paths) {
    auto fmt = lspp::Format::get_format(p);
    auto name = p.filename();
    lspp::LongListing ll(p, pad);
    std::cout << "constructing long listing\n";
    lspp::FormattedPath fp(name, fmt, ll, pad);
    std::cout << "constructing formatted path\n";
    std::cout << fp << "\n";
  }
  return 0;
}
