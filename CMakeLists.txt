project(BaleUri)

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

add_subdirectory(src)
# add_subdirectory(include)
add_subdirectory(test)
add_subdirectory(lib/googletest)