project('lspp', 'cpp', default_options : ['cpp_std=c++17'])

cc = meson.get_compiler('cpp')

fs_dep = cc.find_library('stdc++fs', required : true)

asan_dep = cc.find_library('asan', required : true)

incdir = include_directories('include')

sources = ['src/main.cc', 'src/format.cc', 'src/formattedPath.cc', 'src/longListing.cc', 'src/padding.cc']

cxx_args = ['-fsanitize=address', '-Wall', '-Wextra']

executable('lspp', sources, dependencies : [fs_dep, asan_dep], include_directories : incdir, cpp_args: cxx_args)
