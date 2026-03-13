file(GLOB_RECURSE sources "*.cpp" "*.h")

add_executable(aib ${sources})

generic_includes(aib)

target_link_libraries(aib
  util
  json
)

install(TARGETS aib DESTINATION ${CMAKE_INSTALL_BINDIR})
