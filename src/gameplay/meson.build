gameplay_lib = static_library('cxxess_gameplay', ['board.cpp', 'piece.cpp'],
                              include_directories: [gameplay_includes])

gameplay_dep = declare_dependency(link_with : gameplay_lib,
                                  include_directories : [gameplay_includes])