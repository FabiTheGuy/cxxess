project('cxxess', 
  'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

cmake = import('cmake')

sfml_proj = cmake.subproject('sfml')
sfml_graphics_dep = sfml_proj.dependency('sfml-graphics')
sfml_sys_dep = sfml_proj.dependency('sfml-system')
sfml_window_dep = sfml_proj.dependency('sfml-window')

sfml_dep = declare_dependency(dependencies: [sfml_graphics_dep, sfml_sys_dep, sfml_window_dep])

slotmap_includes = include_directories('subprojects/slotmap')
graphics_includes = include_directories('include/graphics')
gameplay_includes = include_directories('include/gameplay')

asset_files = files(
  'assets/king_white.png',
  'assets/queen_white.png',
  'assets/bishop_white.png',
  'assets/knight_white.png',
  'assets/rook_white.png',
  'assets/pawn_white.png',
  'assets/king_black.png',
  'assets/queen_black.png',
  'assets/bishop_black.png',
  'assets/knight_black.png',
  'assets/rook_black.png',
  'assets/pawn_black.png',
)

subdir('src/util')
subdir('src/gameplay')
subdir('src/graphics')

exe = executable('cxxess',
  ['src/main.cpp', 'src/gameplay/board.cpp', 'src/gameplay/piece.cpp'],
  dependencies: [ graphics_dep ],
  include_directories : include_directories('include/'),
  install : true)

test('basic', exe)
