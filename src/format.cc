
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
