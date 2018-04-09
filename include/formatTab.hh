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

#ifndef INCLUDE_FORMATTAB_HH_
#define INCLUDE_FORMATTAB_HH_

#include <experimental/filesystem>
#include <map>
#include <string>

#include "format.hh"

namespace fs = std::experimental::filesystem;

namespace lspp {

enum class FS_FILE_TYPE {
  FILE,
  DIR,
  BLK_DEV,
  CHR_DEV,
  SOCK,
  FIFO,
};

const std::map<const std::string, Format> ext_format = {
  {".",          {"",      ""}},
  {".exe",       {"",      ""}},
  {".out",       {"",      ""}},
  {".jar",       {"",      ""}},

  {".7z",        {"",      ""}},
  {".bz",        {"",      ""}},
  {".bz2",       {"",      ""}},
  {".gz",        {"",      ""}},
  {".tar",       {"",      ""}},
  {".xz",        {"",      ""}},
  {".zip",       {"",      ""}},

  {".ai",        {"",      ""}},
  {".bmp",       {"",      ""}},
  {".gif",       {"",      ""}},
  {".ico",       {"",      ""}},
  {".jpeg",      {"",      ""}},
  {".jpg",       {"",      ""}},
  {".png",       {"",      ""}},
  {".psb",       {"",      ""}},
  {".psd",       {"",      ""}},

  {".mp3",       {"",      ""}},
  {".wav",       {"",      ""}},
  {".mkv",       {"",      ""}},

  {".doc",       {"",      ""}},
  {".docx",      {"",      ""}},
  {".odp",       {"",      ""}},
  {".ods",       {"",      ""}},
  {".odt",       {"",      ""}},
  {".pdf",       {"",      ""}},
  {".ppt",       {"",      ""}},
  {".pptx",      {"",      ""}},
  {".ttf",       {"",      ""}},
  {".xls",       {"",      ""}},
  {".xlsx",      {"",      ""}},
  {".csv",       {"",      ""}},
  {".dump",      {"",      ""}},
  {".log",       {"",      ""}},
  {".markdown",  {"",      ""}},
  {".md",        {"",      ""}},
  {".rss",       {"",      ""}},
  {".t",         {"",      ""}},
  {".txt",       {"",      ""}},
  {".xml",       {"",      ""}},
  {".yaml",      {"",      ""}},

  {".conf",      {"",      ""}},
  {".pro",       {"",      ""}},

  {".lock",      {"\uf023", ""}},
  {".swp",       {"",      ""}},
  {".tmp",       {"",      ""}},

  {".class",     {"",      ""}},
  {".o",         {"",      ""}},

  {".asm",       {"",      ""}},
  {".S",         {"",      ""}},
  {".s",         {"",      ""}},
  {".bash",      {"",      ""}},
  {".bat",       {"",      ""}},
  {".c",         {"",      ""}},
  {".h",         {"",      ""}},
  {".cc",        {"",      ""}},
  {".c++",       {"",      ""}},
  {".cpp",       {"",      ""}},
  {".hh",        {"",      ""}},
  {".hpp",       {"",      ""}},
  {".inl",       {"",      ""}},
  {".clj",       {"",      ""}},
  {".cljc",      {"",      ""}},
  {".cljs",      {"",      ""}},
  {".coffee",    {"",      ""}},
  {".cp",        {"",      ""}},
  {".csh",       {"",      ""}},
  {".css",       {"",      ""}},
  {".cxx",       {"",      ""}},
  {".d",         {"",      ""}},
  {".dart",      {"",      ""}},
  {".db",        {"",      ""}},
  {".diff",      {"",      ""}},
  {".edn",       {"",      ""}},
  {".ejs",       {"",      ""}},
  {".erl",       {"",      ""}},
  {".f#",        {"",      ""}},
  {".fish",      {"",      ""}},
  {".fs",        {"",      ""}},
  {".fsi",       {"",      ""}},
  {".fsscript",  {"",      ""}},
  {".fsx",       {"",      ""}},
  {".go",        {"",      ""}},
  {".hbs",       {"",      ""}},
  {".hrl",       {"",      ""}},
  {".hs",        {"",      ""}},
  {".htm",       {"",      ""}},
  {".html",      {"",      ""}},
  {".ini",       {"",      ""}},
  {".java",      {"",      ""}},
  {".jl",        {"",      ""}},
  {".js",        {"",      ""}},
  {".json",      {"",      ""}},
  {".jsx",       {"",      ""}},
  {".less",      {"",      ""}},
  {".lhs",       {"",      ""}},
  {".lua",       {"",      ""}},
  {".ml",        {"λ",      ""}},
  {".mli",       {"λ",      ""}},
  {".sml",       {"λ",      ""}},
  {".mustache",  {"",      ""}},
  {".php",       {"",      ""}},
  {".pl",        {"",      ""}},
  {".pm",        {"",      ""}},
  {".py",        {"",      ""}},
  {".pyc",       {"",      ""}},
  {".pyd",       {"",      ""}},
  {".pyo",       {"",      ""}},
  {".rb",        {"",      ""}},
  {".rlib",      {"",      ""}},
  {".rs",        {"",      ""}},
  {".scala",     {"",      ""}},
  {".scm",       {"λ",      ""}},
  {".scss",      {"",      ""}},
  {".sh",        {"",      ""}},
  {".slim",      {"",      ""}},
  {".sln",       {"",      ""}},
  {".sql",       {"",      ""}},
  {".styl",      {"",      ""}},
  {".suo",       {"",      ""}},
  {".tex",       {"",      ""}},
  {".ts",        {"",      ""}},
  {".twig",      {"",      ""}},
  {".v",         {"λ",      ""}},
  {".vim",       {"",      ""}},
  {".xul",       {"",      ""}},
  {".yml",       {"",      ""}},
  {".zsh",       {"",      ""}},
};

const std::map<const std::string, Format> name_format = {
  {"Makefile",          {"",      ""}},
};

const std::map<fs::file_type, Format> fs_type_format = {
  {fs::file_type::regular,     {"", ""}},
  {fs::file_type::directory,   {"", ""}},
  {fs::file_type::block,       {"", ""}},
  {fs::file_type::character,   {"", ""}},
  {fs::file_type::socket,      {"", ""}},
  {fs::file_type::fifo,        {"", ""}},
  {fs::file_type::symlink,     {"", ""}},
  {fs::file_type::none,        {"", ""}},
  {fs::file_type::not_found,   {"", ""}},
  {fs::file_type::unknown,     {"", ""}},
};


}  // namespace lspp
#endif  // INCLUDE_FORMATTAB_HH_
