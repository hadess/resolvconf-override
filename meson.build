project(
  'resolvconf-override', 'c',
  version: '1.0',
  license: 'LGPL2.1+',
  default_options: 'buildtype=debugoptimized',
  meson_version: '>= 0.46.0'
)

cc = meson.get_compiler('c')
libdl = cc.find_library('dl')

shared_library(
    'gettext-pseudolocale',
    sources: [ 'resolvconf-override.c' ],
    dependencies: libdl,
    install: false
)
