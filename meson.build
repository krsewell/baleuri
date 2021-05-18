project('baleuri', 'cpp',
  version: '0.1.0',
  license: 'MIT')

includes = include_directories('include')

subdir('include')
subdir('src')
subdir('test')


test_uri_absolute = executable('test_uri_absolute', 'test/uri_absolute_test.cpp')
test('uri_absolute', test_uri_absolute)
