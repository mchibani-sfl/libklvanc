cmake_minimum_required(VERSION 3.13)
project(klvanc)

set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(klvanc_sources *.c)
set(klvanc_include_dir ${CMAKE_SOURCE_DIR})

message("Root dir: ${CMAKE_SOURCE_DIR}")
message("Lib dir: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

FILE(GLOB klvanc_sources *.c)

add_library(klvanc
  STATIC ${klvanc_sources}
)

target_include_directories(klvanc
  PUBLIC ${klvanc_include_dir}
)

target_link_libraries(klvanc PUBLIC STATIC)

add_compile_options("-Wall -O3")
add_compile_options("-D_FILE_OFFSET_BITS=64 -D_DEFAULT_SOURCE")
