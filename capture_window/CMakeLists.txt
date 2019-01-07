# CMakeList.txt : CMake project for capture_window, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (capture_window "capture_window.cpp" "capture_window.h")

include_directories(capture_window, "../thirdparty")
# TODO: Add tests and install targets if needed.
