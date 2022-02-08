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

message("Root dir: ${CMAKE_SOURCE_DIR}")
message("Lib dir: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

if(UNIX)
FILE(GLOB klvanc_sources RELATIVE ${CMAKE_SOURCE_DIR} *.c)

set(executables 
 klvanc_util
 klvanc_parse
 klvanc_smpte2038
 klvanc_scte104
 klvanc_genscte104
 klvanc_eia708
 klvanc_smpte12_2
 klvanc_afd
 )
else()
# TODO. On Windows, only enable smpte12_2 for now. The others need more work.
set(klvanc_sources smpte12_2.c)
set(executables klvanc_smpte12_2)
endif()

 # Set OS specific config
 if(UNIX)
  set(os_spec_libs -pthread)
 else()
  set(os_spec_libs "")
 endif()

 foreach(item ${executables})
 message("Building ${item}")
 add_executable(${item} 
 ${klvanc_sources}
 )
 target_include_directories(${item} 
 PUBLIC ${klvanc_inc_dir}
 )
 target_link_directories(${item} 
 PUBLIC ${klvanc_lib_dir}
 )
 target_link_libraries(${item} -lklvanc ${os_spec_libs})
 endforeach()
 
# Set c flags
add_compile_options(-Wall -O3)
 
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


