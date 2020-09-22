# Tell to CMake where our includes are
include_directories( ${CMAKE_SOURCE_DIR}/include )

# Get all sources (using recursivity)
file( GLOB_RECURSE PRJ_SOURCES *.cpp *.c )

# Get all headers (using recursivity)
file( GLOB_RECURSE PRJ_HEADERS *.hpp *.h )

# Create exec by giving him all sources and headers
add_executable( OpenCVVideoStream ${PRJ_SOURCES} ${PRJ_HEADERS} )

# Link the libs we are using
target_link_libraries( OpenCVVideoStream ${OpenCV_LIBS} )
# target_link_libraries(main PRIVATE quirc opencv_ml opencv_dnn opencv_core)