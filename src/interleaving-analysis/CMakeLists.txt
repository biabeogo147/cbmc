file(GLOB_RECURSE sources "*.cpp" "*.h")

add_library(interleaving-analysis-lib ${sources})

generic_includes(interleaving-analysis-lib)

target_link_libraries(interleaving-analysis-lib
    goto-programs
    pointer-analysis
    analyses
    langapi
    util
)
