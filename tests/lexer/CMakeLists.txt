add_executable(lexer_tests ident_test.cpp label_test.cpp ../../src/lexer.h ../../src/lexer.cpp)
target_include_directories(lexer_tests PRIVATE ../../src)
target_link_libraries(lexer_tests gtest_main fmt::fmt)

include(GoogleTest)
gtest_discover_tests(lexer_tests)
