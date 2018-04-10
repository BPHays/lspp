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

#include <optional>
#include <iostream>

#include "formatTab.hh"
#include "format.hh"

namespace lspp {

static std::optional<Format> get_format_from_extension(const fs::path & p) {
  const auto ext = p.extension();
  const auto it = ext_format.find(ext);
  if (ext_format.end() != it) {
    return it->second;
  } else {
    return std::nullopt;
  }
}

static std::optional<Format> get_format_from_name(const fs::path & p) {
  const auto name = p.filename();
  const auto it = name_format.find(name);
  if (name_format.end() != it) {
    return it->second;
  } else {
    return std::nullopt;
  }
}

static std::optional<Format> get_format_from_fs_type(const fs::path & p) {
  const auto it = fs_type_format.find(fs::status(p).type());
  if (fs_type_format.end()  != it) {
    return it->second;
  } else {
    return std::nullopt;
  }
}

std::ostream& operator<<(std::ostream& os, const Format& f) {
  if (nullptr != f.get_icon()) {
    os << f.get_icon() << " ";
  }
  if (nullptr != f.get_ansi_seq()) {
    os << f.get_ansi_seq();
  }
  return os;
}

Format Format::get_format(const fs::path& p) {
  return get_format_from_name(p).
    value_or(get_format_from_extension(p).
    value_or(get_format_from_fs_type(p).
    value_or(empty_format)));
}

}  // namespace lspp
