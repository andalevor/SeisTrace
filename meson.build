project('SeisTrace', 'c',
  version : '0.0.2',
  license : 'LGPL',
  default_options : ['c_std=c11'])
inc = include_directories('include', 'extern/mlib')
subdir('include')
subdir('src')
subdir('test')
pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : SeisTrace,
  version : '0.0.2',
  name : 'libseistrace',
  filebase : 'seistrace',
  description : 'A library for seismic trace manipulation.')
