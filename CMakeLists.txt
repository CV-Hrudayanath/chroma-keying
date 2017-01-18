cmake_minimum_required(VERSION 2.8)
project( chroma )
find_package( OpenCV REQUIRED )
add_executable( chroma chroma.cpp )
target_link_libraries( chroma ${OpenCV_LIBS} )

