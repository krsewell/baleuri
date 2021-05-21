test_sources = ['test_runner.cpp', 'uri_utils_test.cpp']

gtest_dep = dependency('gtest', main: true, required: false)
gmock_dep = dependency('gmock', required: false)

test_runner = executable('test_runner', test_sources, include_directories: includes, dependencies: gtest_dep, link_with: baleuri)
test('baleuri test', test_runner)