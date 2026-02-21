#include "parser.h"
#include "tokens.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

using namespace Asm4004;

TEST(Parser, NormalInstruction) {
    std::vector<Token> tokens = {Identifier{"ldm"}, Integer{10}, Identifier{"xch"},
                                 Identifier{"r0"}};
    Parser parser{tokens};

    std::vector<Instruction> expected = {
        {{10, 0}, "ldm"},
        {{0, 0}, "xch"},
    };

    ASSERT_EQ(parser.parse(), expected);
}

TEST(Parser, InstructionWithoutArg) {
    std::vector<Token> tokens = {Identifier{"ldm"}, Integer{10}, Identifier{"xch"}};
    Parser parser{tokens};

    ASSERT_THROW(parser.parse(), std::runtime_error);
}

TEST(Parser, InstructionWithWrongArg) {
    std::vector<Token> tokens = {Identifier{"ldm"}, Identifier{"r0"}};
    Parser parser{tokens};

    ASSERT_THROW(parser.parse(), std::invalid_argument);
}

TEST(Parser, UnexpectedInstruction) {
    std::vector<Token> tokens = {Identifier{"any"}, Identifier{"r0"}};
    Parser parser{tokens};

    ASSERT_THROW(parser.parse(), std::runtime_error);
}
