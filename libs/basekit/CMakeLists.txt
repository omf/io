# Base Io build system
# Written by Jeremy Tregunna <jeremy.tregunna@me.com>
#
# Build the garbage collector library.

# Output our dynamic library to the top-level _build hierarchy
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/_build/dll)

# Marvelous flags, likely compiler dependent.
add_definitions("-DBUILDING_BASEKIT_DLL")

# Include dirs, -I flags and whatnot
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/simd_cph/include)

# Our library sources.
file(GLOB SRCS "source/*.c")

# Now build the shared library
add_library(basekit SHARED ${SRCS})

# ...And the static library
#add_library(basekit_static STATIC ${SRCS})

# The following add the install target, so we put libbasekit.* in our
# install prefix.
install(TARGETS basekit DESTINATION lib)
