# Set OS specific config
if(UNIX)
message("Generating project files for UNIX (Makefile)")
elseif(MSVC)
message("Generating project files for Windows (MSVC)")
else()
message(FATAL_ERROR "Unsupported platform")
endif()

set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED TRUE)

# Set c flags
add_compile_options(-Wall -O3)

# Set OS specific config
if(UNIX)
  # Use PIC even if we are building static lib, in case it's 
  # used to produce a shared lib.
  add_compile_options(-fPIC)
  add_compile_definitions(_FILE_OFFSET_BITS=64 _DEFAULT_SOURCE _POSIX_ ENABLE_RESTRICTED_CODE_PATH ENABLE_VANC_CACHE)
else()
  add_compile_definitions(__inline__=inline)
endif()
