project('cxxess', 
  'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

cmake = import('cmake')

sfml_proj = cmake.subproject('sfml')

sfml_dep = sfml_proj.dependency('sfml-graphics')

exe = executable('cxxess',
  ['src/main.cpp'],
  dependencies: [ sfml_dep ],
  include_directories : include_directories('include/'),
  install : true)

test('basic', exe)
