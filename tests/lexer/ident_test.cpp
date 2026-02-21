#include "lexer.h"
#include "tokens.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

using namespace Asm4004;

TEST(Lexer, EmptyIdentifier) {
    std::string code = "";
    Lexer lexer(code);
    auto tokens = lexer.tokenize();
    EXPECT_TRUE(tokens.empty());
}

TEST(Lexer, IdentifierWithUndefinedSymbols) {
    std::string code = "xch..asd";
    Lexer lexer(code);
    ASSERT_THROW(lexer.tokenize(), std::runtime_error);
}

TEST(Lexer, RandomIdentifiers) {
    std::string code = "chx any vdo";
    Lexer lexer(code);
    std::vector<Token> expected = {
        Identifier{"chx"},
        Identifier{"any"},
        Identifier{"vdo"},
    };

    ASSERT_EQ(lexer.tokenize(), expected);
}

TEST(Lexer, NormalInput) {
    std::string code = "ldm 5\nxch r0";
    Lexer lexer(code);

    std::vector<Token> expected = {
        Identifier{"ldm"},
        Integer{5},
        Identifier{"xch"},
        Identifier{"r0"},
    };

    ASSERT_EQ(lexer.tokenize(), expected);
}
