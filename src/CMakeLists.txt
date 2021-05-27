add_library(baleuri SHARED UriUtils.cpp Uri.cpp)
add_library(bale::uri ALIAS baleuri)

target_compile_features(baleuri PRIVATE )


target_include_directories(baleuri
        PUBLIC
            ${PROJECT_SOURCE_DIR}/include)
