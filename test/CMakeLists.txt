enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(test_runner test_runner.cpp uri_utils_test.cpp)
target_include_directories(test_runner PUBLIC ${GTEST_INCLUDE_DIRS})

target_link_libraries(test_runner
        PUBLIC
          baleuri
          ${GTEST_BOTH_LIBRARIES}
        PRIVATE
          Threads::Threads)

include(GoogleTest)
gtest_discover_tests(test_runner)