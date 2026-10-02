# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "src/CMakeFiles/clipsnap_autogen.dir/AutogenUsed.txt"
  "src/CMakeFiles/clipsnap_autogen.dir/ParseCache.txt"
  "src/clipsnap_autogen"
  "tests/CMakeFiles/TestHistory_autogen.dir/AutogenUsed.txt"
  "tests/CMakeFiles/TestHistory_autogen.dir/ParseCache.txt"
  "tests/TestHistory_autogen"
  )
endif()
