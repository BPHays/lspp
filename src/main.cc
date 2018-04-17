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

#include <sys/ioctl.h>
#include <unistd.h>

#include <experimental/filesystem>
#include <optional>
#include <algorithm>
#include <iostream>
#include <functional>

#include <tclap/CmdLine.h>

#include "format.hh"
#include "formattedPath.hh"
#include "longListing.hh"
#include "padding.hh"

namespace fs = std::experimental::filesystem;

namespace lspp {

typedef std::function<void(const fs::path&, const lspp::Format&,
    const Padding&)> printer;

void short_printer(const fs::path& path, const lspp::Format& fmt,
    const Padding& pad) {
  auto name = path.filename();
  lspp::FormattedPath fp(name, fmt);
  std::cout << fp << "\n";
}

std::size_t short_length(const fs::path& path, const lspp::Format& fmt) {
  auto name = path.filename();
  lspp::FormattedPath fp(name, fmt);
  return fp.get_length();
}

void long_printer(const fs::path& path, const lspp::Format& fmt,
    const Padding& pad) {
  auto name = path.filename();
  lspp::LongListing ll(path, pad);
  lspp::FormattedPath fp(name, fmt, ll, pad);
  std::cout << fp << "\n";
}

std::size_t long_length(const fs::path& path, const lspp::Format& fmt) {
  auto name = path.filename();
  lspp::LongListing ll(path);
  lspp::FormattedPath fp(name, fmt, ll);
  return fp.get_length();
}

void print_single(const std::vector<fs::path>& paths, const Padding& pad,
  printer print) {
  // Print the paths in a single column
  for (auto const & p : paths) {
    auto fmt = lspp::Format::get_format(p);
    auto name = p.filename();
    print(p, fmt, pad);
  }
}

// Get the terminal width
std::size_t get_terminal_width() {
  struct winsize w;
  int retval = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  if (0 == retval) {
    return w.ws_col;
  } else {
    perror(__func__);
    // TODO(brian) actually throw here
    return 0;
  }
}

// Test if the current set of paths would fit in n columns given a terminal
// of width term_width.
// If the paths would fit then return the padding required for each column
// else return an empty optional to imply no solution could be found
auto test_width(
    const std::vector<fs::path>& paths, const std::size_t term_width,
    const std::size_t n_cols, const Padding& pad) {
  std::size_t total_width = 0;
  auto col_widths = std::vector<std::size_t>(n_cols, 0);

  for (std::size_t i = 0; i < paths.size(); i += n_cols) {
    for (std::size_t col = 0;
         total_width < term_width && col < n_cols && i + col < paths.size();
         ++col) {
      auto const& path = paths[i + col];
      auto fmt = lspp::Format::get_format(path);
      std::size_t len = long_length(path, fmt);

      //std::size_t len = paths[i + col].filename().string().length();
      if (len > col_widths[col]) {
        total_width -= col_widths[col];
        total_width += len;
        col_widths[col] = len;
      }
    }
  }

  return total_width + (n_cols - 1) < term_width ?
    std::make_optional(col_widths) : std::nullopt;
}

void print_columns(const std::vector<fs::path>& paths, const Padding& pad,
    bool longListing) {
  // Find the largest size which works
  std::size_t term_width = get_terminal_width();

  // Try to find the maximum number of columns that will fit on the terminal
  std::size_t n_cols = term_width;
  std::optional<std::vector<std::size_t>> col_widths = std::nullopt;
  do {
    col_widths = test_width(paths, term_width, n_cols, pad);
  } while (!col_widths && 0 < n_cols--);

  // Actually print the paths
  for (std::size_t i = 0; i < paths.size(); ++i) {
    // Print the path itself
    auto name = paths[i].filename();
    auto fmt = lspp::Format::get_format(paths[i]);
    lspp::LongListing ll(paths[i], pad);
    lspp::FormattedPath fp(name, fmt, ll);
    std::cout << std::left << std::setw((*col_widths)[i % col_widths->size()])
      << fp;

    //  std::cout << std::left << std::setw((*col_widths)[i % col_widths->size()])
    //    << paths[i].filename().string();

    // Print whatever whitespace is required
    if (col_widths->size() - 1 == i % col_widths->size()) {
      // If the end of a row then add a newline
      std::cout << "\n";
    } else if (i != paths.size()) {
      // If any path in the middle of a row print a space
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}

}  // namespace lspp

int main(int argc, char ** argv) {
  TCLAP::CmdLine cmd("List Directory Contents", ' ', "0.0");
  TCLAP::SwitchArg longSwitch("l", "long", "List in long format", cmd, false);
  TCLAP::UnlabeledValueArg
    pathArg("path", "path to list", false, std::string("."), "path");
  cmd.add(pathArg);
  cmd.parse(argc, argv);

  // retreive
  std::vector<fs::path> paths;
  for (auto const & ent : fs::directory_iterator(pathArg.getValue())) {
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

  if (longSwitch.getValue()) {
    lspp::print_single(paths, pad, lspp::long_printer);
  } else {
    // lspp::print_single(paths, pad, lspp::short_printer);
    lspp::print_columns(paths, pad, longSwitch.getValue());
  }
  // lspp::print_columns(paths, pad, longSwitch.getValue());

  return 0;
}
