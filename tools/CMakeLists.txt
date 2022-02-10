cmake_minimum_required(VERSION 3.13)
project(tools_klvanc)

include(../src/common.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(klvanc_sources *.c)
# Might not be the best way
set(klvanc_inc_dir ${CMAKE_SOURCE_DIR}/../src/)
set(klvanc_lib_dir ${CMAKE_SOURCE_DIR}/../src/lib)

message("Source dir: ${CMAKE_SOURCE_DIR}")
message("Lib dir: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("Build type: ${CMAKE_BUILD_TYPE}")

if(UNIX)
  FILE(GLOB klvanc_sources RELATIVE ${CMAKE_SOURCE_DIR} *.c)
  list(REMOVE_ITEM klvanc_sources klvanc_util.c)
else()
  # TODO. On Windows, only enable smpte12_2 for now. The others need more work.
  set(klvanc_sources klvanc_tools.c demo.c smpte12_2.c)
endif()

set(executables klvanc_tools)

 # Set OS specific config
 if(UNIX)
  set(os_spec_libs -pthread)
 else()
  set(os_spec_libs "")
 endif()

add_executable(klvanc_tools ${klvanc_sources})
target_include_directories(klvanc_tools PUBLIC ${klvanc_inc_dir})
if(UNIX)
 target_link_directories(klvanc_tools PUBLIC ${klvanc_lib_dir})
 target_link_libraries(klvanc_tools klvanc ${os_spec_libs})
else()
# Not clean, FIXME. May be use debug macro
 target_link_directories(klvanc_tools PUBLIC ${klvanc_lib_dir}/Debug)
 target_link_directories(klvanc_tools PUBLIC ${klvanc_lib_dir}/Release)
 target_link_libraries(klvanc_tools klvanc ${os_spec_libs})
endif()

# Set OS specific config
if(UNIX)
  message("Configuring for Unix")
  add_compile_definitions(_FILE_OFFSET_BITS=64 _DEFAULT_SOURCE _POSIX_ ENABLE_RESTRICTED_CODE_PATH ENABLE_VANC_CACHE)
elseif(MSVC)
  message("Configuring for MSVC")
  add_compile_definitions(__inline__=inline)
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

