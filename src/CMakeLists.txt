cmake_minimum_required(VERSION 3.8)
project(klvanc)

include(../src/common.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(klvanc_sources *.c)
set(klvanc_include_dir ${CMAKE_SOURCE_DIR})

FILE(GLOB klvanc_sources *.c)

add_library(klvanc
STATIC ${klvanc_sources}
)

target_include_directories(klvanc
PUBLIC ${klvanc_include_dir}
)

target_link_libraries(klvanc PUBLIC STATIC)
