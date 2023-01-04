project('SeisTrace', 'c',
  version : '0.0.1',
  license : 'LGPL')
inc = include_directories('include', 'extern/mlib')
subdir('include')
subdir('src')
subdir('test')
pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : SeisTrace,
  version : '0.0.1',
  name : 'libseistrace',
  filebase : 'seistrace',
  description : 'A library for seismic trace manipulation.')
