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

  LongListing::LongListing(fs::path path, Padding pad) : LongListing(path) {
    std::cout << "LongListing(...)\n";
    pad = pad;
  }

  LongListing::LongListing(fs::path path) : path(path) {
    std::cout << "LongListing(path)\n";
    int retval;

    struct stat stats;
    retval = stat(path.c_str(), &stats);
    if (0 == retval) {
      // query the OS for the file's owner and set the owner field
      char pw_buf[1024];
      struct passwd pw;
      struct passwd* pwp;
      retval = getpwuid_r(stats.st_uid, &pw, pw_buf, sizeof(pw_buf), &pwp);
      if (0 == retval && nullptr != pwp) {
        this->owner = pw.pw_name;
      } else {
        perror("LongListing::LongListing");
        this->owner = "";
      }

      // query the OS for the file's group and set the owner field
      char gr_buf[1024];
      struct group gr;
      struct group* grp;
      retval = getgrgid_r(stats.st_gid, &gr, gr_buf, sizeof(gr_buf), &grp);
      if (0 == retval && nullptr != grp) {
        this->group = gr.gr_name;
      } else {
        perror("LongListing::LongListing");
        this->group = "";
      }
    } else {
      // Handle a stat call failure gracefully
      perror("LongListing::LongListing");
      this->owner = "";
      this->group = "";
    }
  }

  std::uintmax_t LongListing::get_hard_link_count() const {
    return fs::hard_link_count(path);
  }

  std::uintmax_t LongListing::get_file_size() const {
    std::error_code ec;
    return fs::file_size(path, ec);
  }

  fs::perms LongListing::get_permissions() const {
    return fs::status(path).permissions();
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
    if (std::uintmax_t size = ll.get_file_size();
        static_cast<std::uintmax_t>(-1) != size) {
      os << std::setw(pad.size) << size << " ";
      os << pad.size << "\n";
    } else {
      os << std::setw(pad.size) << 0 << " ";
    }
    return os;
  }
}  // namespace lspp
