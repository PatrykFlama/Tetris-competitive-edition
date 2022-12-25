cmake_minimum_required(VERSION 3.10)
project(
  Tetris-competitive-edition
  VERSION 0.1
  LANGUAGES CXX
)

add_executable(tetris-ce src/main.cpp)
target_include_directories(tetris-ce
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
}
