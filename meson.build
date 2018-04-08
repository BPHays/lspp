project('lspp', 'cpp', default_options : ['cpp_std=c++17'])
cc = meson.get_compiler('cpp')
fs_dep = cc.find_library('stdc++fs', required : true)
executable('lspp', 'src/main.cc', dependencies : fs_dep)
