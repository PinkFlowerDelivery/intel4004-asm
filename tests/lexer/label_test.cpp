#include "lexer.h"
#include "tokens.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Asm4004;

TEST(Lexer, NormalLabel) {
    std::string code = "Label: ldm 10";
    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    std::vector<Token> expected = {Label{"Label"}, Identifier{"ldm"}, Integer{10}};

    ASSERT_EQ(tokens, expected);
}

TEST(Lexer, LabelWithoutColon) {
    std::string code = "Label ldm 10";
    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    std::vector<Token> expected = {Identifier{"Label"}, Identifier{"ldm"}, Integer{10}};

    ASSERT_EQ(tokens, expected);
}
