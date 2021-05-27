if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project(BaleUri VERSION 0.0.0 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.20.2)

set(CPP_VERSION 98)
if ("cxx_std_11" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CPP_VERSION 11)
endif()
if ("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CPP_VERSION 14)
endif()
if ("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CPP_VERSION 17)
endif()

# message("Your compiler supports features : ${CMAKE_CXX_COMPILE_FEATURES}")
set(CMAKE_CXX_STANDARD ${CPP_VERSION})
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=clang-analyzer-*,-*,bugprone*,modernize*,performance*,-modernize-pass-by-value,-modernize-use-auto,-modernize-use-using,-modernize-use-trailing-return-type")
set(CMAKE_CXX_CPPCHECK "cppcheck")

find_package(Boost REQUIRED)


add_subdirectory(src)
# add_subdirectory(include)
add_subdirectory(test)
