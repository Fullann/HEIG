# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/pco_bogosort_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/pco_bogosort_autogen.dir/ParseCache.txt"
  "pco_bogosort_autogen"
  )
endif()
