# Minimum cmake version
cmake_minimum_required (VERSION 3.0.0)

# Name of project and that it is C++ only.
project (fastq_finder CXX)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Search for zlib as a dependency for SeqAn.
find_package (ZLIB)

# Load the SeqAn module and fail if not found.
find_package (SeqAn REQUIRED)

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

# Add include directories.
include_directories (${SEQAN_INCLUDE_DIRS})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS  "-static ${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS} -Wl,--whole-archive -Wl,-no-whole-archive")

# Add executable and link against SeqAn dependencies.
add_executable (fastq_finder fastq_finder.cpp)
target_link_libraries (fastq_finder ${SEQAN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
