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

#ifndef INCLUDE_PADDING_HH_
#define INCLUDE_PADDING_HH_

#include <cstddef>
#include <iostream>

namespace lspp {

struct Padding {
  std::size_t permissions = 0;
  std::size_t hard_links = 0;
  std::size_t owner = 0;
  std::size_t group = 0;
  std::size_t size = 0;
  std::size_t modified_date = 0;
  std::size_t file_name = 0;
  bool update_permissions_max(std::size_t permissions);
  bool update_hard_links_max(std::size_t hard_links);
  bool update_owner_max(std::size_t owner);
  bool update_group_max(std::size_t group);
  bool update_size_max(std::size_t size);
  bool update_modified_date_max(std::size_t modified_date);
  bool update_file_name_max(std::size_t file_name);
  std::size_t get_total_width();
};

}  // namespace lspp

#endif  // INCLUDE_PADDING_HH_
