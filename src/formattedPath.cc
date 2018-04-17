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

#include <iostream>

#include "formattedPath.hh"

namespace lspp {

std::size_t FormattedPath::get_length() const {
  std::ostringstream oss;
  oss << *this;
  return oss.str().length();
  /*
  std::string s = oss.str();
  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> ucs2conv;
  std::u16string ucs2 = ucs2conv.from_bytes(s.c_str());
  std::cout << "{" << ucs2.length() << ", " << s << "}\n";
  for(const char * p = s.c_str(); *p != '\0'; ++p) {
    printf("%x ", *p);
  }
  return oss.str().size();
  return ucs2.length();
  */
}

std::ostream& operator<<(std::ostream& os, const FormattedPath& fp) {
  std::ostringstream oss;
  oss << fp.get_fmt();
  if (auto const ll = fp.get_ll(); ll) {
    oss << *ll << " ";
  }
  oss << fp.get_path().string();
  return os << oss.str();
  /*
  os << fp.get_fmt();
  if (auto const ll = fp.get_ll(); ll) {
    os << *ll << " ";
  }
  os << fp.get_path().string();
  // os << FormattedPath::reset_ansi_seq;
  return os;
  */
}

}  // namespace lspp
