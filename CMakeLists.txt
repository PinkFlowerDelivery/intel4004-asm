cmake_minimum_required(VERSION 4.0)

project(i4004asm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        12.1.0)

add_executable(i4004asm src/main.cpp src/lexer.cpp src/tokens.cpp src/parser.cpp)
target_link_libraries(i4004asm fmt::fmt)

# Tests
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(fmt googletest)
enable_testing()

add_executable(lexer_tests tests/lexer/ident_test.cpp src/lexer.cpp src/tokens.cpp)

target_include_directories(lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(lexer_tests GTest::gtest_main fmt::fmt)

include(GoogleTest)

gtest_discover_tests(lexer_tests)
