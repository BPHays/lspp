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

#ifndef INCLUDE_FORMATTEDPATH_HH_
#define INCLUDE_FORMATTEDPATH_HH_

#include <experimental/filesystem>
#include <optional>
#include <iostream>

#include "format.hh"
#include "longListing.hh"
#include "padding.hh"

namespace fs = std::experimental::filesystem;

namespace lspp {

class FormattedPath {
  const fs::path& path;
  const Format& fmt;
  const std::optional<LongListing> ll;
  const Padding pad;
 public:
  const fs::path& get_path() const { return path; }
  const Format& get_fmt() const { return fmt; }
  const std::optional<LongListing>& get_ll() const { return ll; }
  std::size_t get_length() const;
  FormattedPath(const fs::path& path, const Format& fmt,
      const std::optional<LongListing> ll = std::nullopt) :
    path(path), fmt(fmt), ll(ll) { /*std::cout << "fp()\n";*/ }

  FormattedPath(const fs::path& path, const Format& fmt,
      const std::optional<LongListing> ll, Padding pad) :
    path(path), fmt(fmt), ll(ll), pad(pad) { /*std::cout << "fp(pad)\n";*/ }

  constexpr static char const * const reset_ansi_seq = "\033[0m";
};

std::ostream& operator<<(std::ostream& os, const FormattedPath& fp);

}  // namespace lspp

#endif  // INCLUDE_FORMATTEDPATH_HH_
