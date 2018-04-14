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

#include "padding.hh"

namespace lspp {

static bool update_field_max(std::size_t* current, std::size_t candidate) {
  if (candidate > *current) {
    *current = candidate;
    return true;
  } else {
    return false;
  }
}

bool Padding::update_permissions_max(std::size_t permissions) {
  return update_field_max(&this->permissions, permissions);
}

bool Padding::update_hard_links_max(std::size_t hard_links) {
  return update_field_max(&this->hard_links, hard_links);
}

bool Padding::update_owner_max(std::size_t owner) {
  return update_field_max(&this->owner, owner);
}

bool Padding::update_group_max(std::size_t group) {
  return update_field_max(&this->group, group);
}

bool Padding::update_size_max(std::size_t size) {
  return update_field_max(&this->size, size);
}

bool Padding::update_modified_date_max(std::size_t modified_date) {
  return update_field_max(&this->modified_date, modified_date);
}

bool Padding::update_file_name_max(std::size_t file_name) {
  return update_field_max(&this->file_name, file_name);
}

std::size_t Padding::get_total_width() {
  // If a field is present then it has associated padding
  auto const if_present_with_space = [](auto n) {
    return n ? n + 1 : 0;
  };

  // Calculate the total width of all fields
  return if_present_with_space(permissions) +
    if_present_with_space(hard_links) +
    if_present_with_space(owner) +
    if_present_with_space(group) +
    if_present_with_space(size) +
    if_present_with_space(modified_date) +
    if_present_with_space(file_name);
}

}  // namespace lspp
