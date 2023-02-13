set( CMAKE_INCLUDE_PATH "/usr/include/curses.h")
set( CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/libncurses.so")

cmake_minimum_required(VERSION 3.10)
project(
  Tetris-competitive-edition
  VERSION 0.1
  LANGUAGES CXX
)

file(GLOB SOURCES "src/*")

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(tetris ${SOURCES})
set_target_properties(tetris PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(tetris ${CURSES_LIBARIES})
