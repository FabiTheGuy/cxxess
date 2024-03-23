
incbin_exe = executable('incbin_gen', 'incbin_generator.cpp')

incbin_generator = generator(incbin_exe,
                             output  : '@PLAINNAME@.h',
                             arguments : ['@INPUT@', '@OUTPUT@'])