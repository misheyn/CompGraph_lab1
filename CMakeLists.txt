cmake_minimum_required(VERSION 3.20)
project(CompGraph_lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CompGraph_lab1 main.cpp Segments.cpp Segments.h)

target_link_libraries(CompGraph_lab1 -lOpenGL32 -lfreeGLUT -lGLU32)