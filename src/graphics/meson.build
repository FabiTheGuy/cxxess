
asset_incbins = incbin_generator.process(asset_files)

graphics_lib = static_library('cxxess_graphics', ['context.cpp', 'renderer.cpp', asset_incbins],
                              include_directories: [graphics_includes, slotmap_includes],
                              dependencies: [sfml_dep, gameplay_dep])

graphics_dep = declare_dependency(link_with : graphics_lib,
                                  include_directories : [graphics_includes, slotmap_includes],
                                  dependencies : [sfml_dep, gameplay_dep])

exe = executable('cxxess_graphics_test',
                 ['test/renderer_test.cpp'],
                 dependencies: [ graphics_dep ],
                 install : true)