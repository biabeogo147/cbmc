file(GLOB_RECURSE sources "*.cpp" "*.h")
add_library(os-api-lib ${sources})

generic_includes(os-api-lib)

target_link_libraries(os-api-lib util)
