#include "parser.h"
#include "tokens.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

using namespace Asm4004;

TEST(Parser, NormalLabel) {
    std::vector<Token> tokens = {Label{"main"}, Identifier{"ldm"}, Integer{10}, Identifier{"jun"},
                                 Identifier{"main"}};

    Parser parser{tokens};

    std::vector<Instruction> expected = {
        {{10, 0}, "ldm"},
        {{0, 0}, "jun"},
    };

    ASSERT_EQ(parser.parse(), expected);
}

TEST(Parser, UndefinedLabel) {
    std::vector<Token> tokens = {Identifier{"ldm"}, Integer{10}, Identifier{"jun"},
                                 Identifier{"main"}};
    Parser parser{tokens};

    ASSERT_THROW(parser.parse(), std::runtime_error);
}
