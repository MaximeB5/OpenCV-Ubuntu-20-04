# Minimum version of CMake required to use it
cmake_minimum_required( VERSION 3.16 )

# Project name
project( OpenCVVideoStream )

# Minimum C++ version
set( CMAKE_CXX_STANDARD 17 )

# Move the .exe into the Bin folder
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

# Packages needed for the project
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Tell to CMake where our sources are
add_subdirectory( src )