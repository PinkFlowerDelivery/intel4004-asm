add_executable(codegen_tests instr_test.cpp ../../src/codegen.h ../../src/codegen.cpp)
target_include_directories(codegen_tests PRIVATE ../../src)
target_link_libraries(codegen_tests gtest_main fmt::fmt)

include(GoogleTest)
gtest_discover_tests(codegen_tests)
