

include(GoogleTest)
add_executable(test_runner test_runner.cpp uri_utils_test.cpp)

target_link_libraries(test_runner
        baleuri
        gtest_main)

gtest_discover_tests(test_runner)