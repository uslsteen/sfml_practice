cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL)

add_executable(Snake main.cpp snake.cpp snake.h)
target_link_libraries(Snake ${OpenGlLinkers})
