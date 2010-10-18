# Base Io build system
#
# Builds the SHA2 addon

# Create the _build bundle hierarchy if needed.
make_build_bundle(_build)

# Output our dynamic library to the top-level _build hierarchy
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/_build/dll)

# Generate the IoSHA2Init.c file.
# Argument SHOULD ALWAYS be the exact name of the addon, case is
# important.
generate_ioinit(SHA2)

# Our library sources.
set(SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/source/sha2.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/IoSHA256.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/IoSHA2Init.c"
)

# Now build the shared library
add_library(IoSHA2 SHARED ${SRCS})
add_dependencies(IoSHA2 iovmall)
target_link_libraries(IoSHA2 iovmall)

# Install the addon to our global addons hierarchy.
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/io/addons)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/_build DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/io/addons/SHA2)
