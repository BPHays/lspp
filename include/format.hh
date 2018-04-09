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

#ifndef INCLUDE_FORMAT_HH_
#define INCLUDE_FORMAT_HH_

#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace lspp {

class Format {
  char const * const icon;
  char const * const ansi_seq;

 public:
  Format(char const * const icon, char const * const ansi_seq) :
    icon(icon), ansi_seq(ansi_seq) {}
  char const * get_icon() const { return icon; }
  char const * get_ansi_seq() const { return ansi_seq; }

  static Format get_format(const fs::path& p);
};
const Format empty_format {nullptr, nullptr};

std::ostream& operator<<(std::ostream& os, const Format& f);

}  // namespace lspp

#endif  // INCLUDE_FORMAT_HH_
