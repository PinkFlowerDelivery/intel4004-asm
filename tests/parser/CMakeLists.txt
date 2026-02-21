add_executable(parser_tests arg_test.cpp instr_test.cpp ../../src/parser.h ../../src/parser.cpp)
target_include_directories(parser_tests PRIVATE ../../src)
target_link_libraries(parser_tests gtest_main fmt::fmt)

include(GoogleTest)
gtest_discover_tests(parser_tests)
