#include "codegen.h"
#include "parser.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

using namespace Asm4004;

TEST(Codegen, NormalInput) {
    std::vector<Instruction> tokens = {{{10, 0}, "ldm"}, {{0, 0}, "xch"}};
    Codegen codegen{tokens};

    std::vector<uint8_t> expected = {
        0xDA,
        0xB0,
    };

    ASSERT_EQ(codegen.generate(), expected);
}

TEST(Codegen, LongInstruction) {
    std::vector<Instruction> tokens = {
        {{0, 0}, "jun"},
        {{1, 1}, "jms"},
    };
    Codegen codegen{tokens};

    std::vector<uint8_t> expected = {
        0x40,
        0x00,
        0x51,
        0x01,
    };

    ASSERT_EQ(codegen.generate(), expected);
}

TEST(Codegen, LongInstructionWithShortInstruction) {
    std::vector<Instruction> tokens = {
        {{10, 0}, "ldm"},
        {{0, 0}, "xch"},
        {{0, 0}, "jun"},
        {{1, 1}, "jms"},

    };
    Codegen codegen{tokens};

    std::vector<uint8_t> expected = {
        0xDA, 0xB0, 0x40, 0x00, 0x51, 0x01,
    };

    ASSERT_EQ(codegen.generate(), expected);
}

TEST(Codegen, JcnGoto) {
    std::vector<Instruction> tokens = {
        {{10, 0}, "ldm"},
        {{0, 0}, "xch"},
        {{4, 4}, "jcn"},
        {{0, 0}, "add"},
    };
    Codegen codegen{tokens};

    std::vector<uint8_t> expected = {0xDA, 0xB0, 0x14, 0x04, 0x80};

    ASSERT_EQ(codegen.generate(), expected);
}
