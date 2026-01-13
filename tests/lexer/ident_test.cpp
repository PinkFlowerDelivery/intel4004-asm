#include "lexer.h"
#include "tokens.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

using namespace Asm4004;

TEST(Lexer, EmptyIdentifier) {
  std::string code = "";
  Lexer lexer(code);
  auto tokens = lexer.tokenize();
  EXPECT_TRUE(tokens.empty());
}

TEST(Lexer, IdentifierWithUndefinedSymbols) {
  std::string code = "xch_asd";
  Lexer lexer(code);
  ASSERT_THROW(lexer.tokenize(), std::runtime_error);
}

TEST(Lexer, RandomIdentifiers) {
  std::string code = "chx any vdo";
  Lexer lexer(code);
  std::vector<Asm4004::Token> expected = {
      Asm4004::Identifier{"chx"},
      Asm4004::Identifier{"any"},
      Asm4004::Identifier{"vdo"},
  };

  ASSERT_EQ(lexer.tokenize(), expected);
}

TEST(Lexer, NormalInput) {
  std::string code = "ldm 5 ; xch r0;";
  Lexer lexer(code);

  std::vector<Asm4004::Token> expected = {
      Asm4004::Identifier{"ldm"}, Asm4004::Integer{5},
      Asm4004::Semicolon{},       Asm4004::Identifier{"xch"},
      Asm4004::Identifier{"r0"},  Asm4004::Semicolon{},
  };

  ASSERT_EQ(lexer.tokenize(), expected);
}
