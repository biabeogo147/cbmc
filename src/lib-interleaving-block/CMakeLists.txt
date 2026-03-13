file(GLOB_RECURSE sources "*.cpp" "*.h")

add_executable(aib ${sources})

set_target_properties(aib PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

install(TARGETS aib DESTINATION ${CMAKE_INSTALL_BINDIR})
