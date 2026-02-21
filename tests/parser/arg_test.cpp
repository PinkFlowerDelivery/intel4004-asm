#include "parser.h"
#include "tokens.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

using namespace Asm4004;

TEST(Parser, NormalArgs) {
    std::vector<Token> tokens = {Identifier{"ldm"}, Integer{10}};
    Parser parser{tokens};

    std::vector<Instruction> expected = {
        {{10, 0}, "ldm"},
    };

    ASSERT_EQ(parser.parse(), expected);
}

TEST(Parser, Normal2Args) {
    std::vector<Token> tokens = {Identifier{"fim"}, Identifier{"r0"}, Comma{}, Integer{10}};
    Parser parser{tokens};

    std::vector<Instruction> expected = {
        {{0, 10}, "fim"},
    };

    ASSERT_EQ(parser.parse(), expected);
}

TEST(Parser, ArgsWithoutComma) {
    std::vector<Token> tokens = {Identifier{"fim"}, Identifier{"r0"}, Integer{32}};

    Parser parser{tokens};

    ASSERT_THROW(parser.parse(), std::runtime_error);
}

TEST(Parser, MissingSecondOperand) {
    std::vector<Token> tokens = {Identifier{"fim"}, Identifier{"r0"}};

    Parser parser{tokens};

    ASSERT_THROW(parser.parse(), std::runtime_error);
}

TEST(Parser, InstructionWith2DifferentOperands) {
    std::vector<Token> tokens = {Label{"main"},     Identifier{"ldm"}, Integer{10},
                                 Identifier{"isz"}, Identifier{"r0"},  Comma{},
                                 Identifier{"main"}};
    Parser parser{tokens};

    std::vector<Instruction> expected = {
        {{10, 0}, "ldm"},
        {{0, 0}, "isz"},
    };

    ASSERT_EQ(parser.parse(), expected);
}
