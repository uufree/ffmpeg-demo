cmake_minimum_required(VERSION 3.14)
project(sdl)

# system setting
# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-pthread -std=c++11")

include_directories(./include)
include_directories(/usr/local/Cellar/sdl2/2.0.14_1/include)
include_directories(/usr/local/Cellar/ffmpeg/4.3.1_9/include)
#include_directories(/usr/local/include)
link_directories(/usr/local/Cellar/sdl2/2.0.14_1/lib)
#link_directories(/usr/local/lib)
link_directories(/usr/local/Cellar/ffmpeg/4.3.1_9/lib)

file(GLOB SRC_FILES src/*.cc)

add_executable(sdl ${SRC_FILES})
target_link_libraries(sdl avformat avdevice avcodec avutil swresample avfilter swscale)