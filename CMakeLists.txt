cmake_minimum_required(VERSION 4.0)

project(4004asm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        12.1.0)

FetchContent_MakeAvailable(fmt)

add_executable(main src/main.cpp src/lexer.cpp src/tokens.cpp src/parser.cpp)

target_link_libraries(main fmt::fmt)
