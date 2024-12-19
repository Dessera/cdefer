project(
  'cdefer',
  'c',
  version: '0.1',
  default_options: ['warning_level=3', 'c_std=gnu23'],
)

install_headers('include/cdefer.h', subdir: 'cdefer')

pkg = import('pkgconfig')
pkg.generate(
  name: 'cdefer',
  description: 'A simple C library for defer statement',
  version: '0.1',
  subdirs: ['cdefer'],
)

cc = meson.get_compiler('c')

c_args = []
if cc.get_id() == 'clang'
  c_args += '-fblocks'
endif

test_cdefer = executable(
  'test_cdefer',
  'tests/test_cdefer.c',
  include_directories: include_directories('include'),
  c_args: c_args,
)

test('test_cdefer', test_cdefer)