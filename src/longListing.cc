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

#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <cstdio>

#include <iomanip>

#include "longListing.hh"

namespace lspp {

bool LongListing::query_os_for_user(const struct stat& stats) {
  char pw_buf[1024];
  struct passwd pw;
  struct passwd* pwp;

  int retval = getpwuid_r(stats.st_uid, &pw, pw_buf, sizeof(pw_buf), &pwp);
  if (0 == retval && nullptr != pwp) {
    this->owner = pw.pw_name;
    return true;
  } else {
    perror("LongListing::LongListing");
    this->owner = "";
    return false;
  }
}

bool LongListing::query_os_for_group(const struct stat& stats) {
  char gr_buf[1024];
  struct group gr;
  struct group* grp;
  int retval = getgrgid_r(stats.st_gid, &gr, gr_buf, sizeof(gr_buf), &grp);
  if (0 == retval && nullptr != grp) {
    this->group = gr.gr_name;
    return true;
  } else {
    perror("LongListing::LongListing");
    this->group = "";
    return false;
  }
}

bool LongListing::query_os_for_user_and_group(const fs::path& path) {
  struct stat stats;
  int retval = stat(path.c_str(), &stats);
  if (0 == retval) {
    return query_os_for_user(stats) && query_os_for_group(stats);
  } else {
    perror("LongListing::LongListing");
    this->owner = "";
    this->group = "";
    return false;
  }
}

LongListing::LongListing(fs::path path, Padding pad) : LongListing(path) {
  this->pad = pad;
}

LongListing::LongListing(fs::path path) : path(path) {
  query_os_for_user_and_group(path);
}

std::uintmax_t LongListing::get_hard_link_count() const {
  return fs::hard_link_count(path);
}

std::uintmax_t LongListing::get_file_size() const {
  std::error_code ec;
  if (std::uintmax_t size = fs::file_size(path, ec);
      static_cast<std::uintmax_t>(-1) != size) {
    return size;
  } else {
    return 0;
  }
}

fs::perms LongListing::get_permissions() const {
  return fs::status(path).permissions();
}

std::size_t LongListing::get_length() const {
  std::ostringstream oss;
  oss << *this;
  return oss.str().length();
}

static std::ostream& operator<<(std::ostream& os, const fs::perms p) {
  return os
    << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
    << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
    << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
    << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
    << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
    << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
    << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
    << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
    << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-");
}

std::ostream& operator<<(std::ostream& os, const LongListing ll) {
  const Padding& pad = ll.get_pad();
  os << ll.get_permissions() << " ";
  os << std::setw(pad.hard_links) << ll.get_hard_link_count() << " ";
  os << std::setw(pad.owner) << ll.get_owner() << " ";
  os << std::setw(pad.group) << ll.get_group() << " ";
  os << std::setw(pad.size) << ll.get_file_size() << " ";
  return os;
}

}  // namespace lspp
