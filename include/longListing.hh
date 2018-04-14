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

#ifndef INCLUDE_LONGLISTING_HH_
#define INCLUDE_LONGLISTING_HH_

#include <experimental/filesystem>
#include <iostream>
#include <string>

#include "padding.hh"

namespace fs = std::experimental::filesystem;

namespace lspp {

class LongListing {
  fs::path path;
  std::string owner;
  std::string group;
  Padding pad;
  bool query_os_for_user(const struct stat& stats);
  bool query_os_for_group(const struct stat& stats);
  bool query_os_for_user_and_group(const fs::path& path);
 public:
  explicit LongListing(fs::path path);
  explicit LongListing(fs::path path, Padding pad);
  const fs::path& get_path() const { return path; }
  const std::string get_owner() const { return owner; }
  const std::string get_group() const { return group; }
  const Padding get_pad() const { return pad; }
  std::uintmax_t get_hard_link_count() const;
  std::uintmax_t get_file_size() const;
  fs::perms get_permissions() const;
};

std::ostream& operator<<(std::ostream& os, const LongListing ll);

}  // namespace lspp

#endif  // INCLUDE_LONGLISTING_HH_
