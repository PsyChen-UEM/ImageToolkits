# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ImageToolkits_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ImageToolkits_autogen.dir\\ParseCache.txt"
  "ImageToolkits_autogen"
  )
endif()
