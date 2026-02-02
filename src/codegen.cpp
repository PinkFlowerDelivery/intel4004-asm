#include "codegen.h"

std::unordered_map<std::string, opcodeData> opcodeTable = {
    {"nop", {0x00, 0}}, {"jcn", {0x1, 2}},  {"fim", {0x2, 2}},  {"fin", {0x3, 1}},
    {"jin", {0x3, 1}},  {"jun", {0x4, 2}},  {"jms", {0x5, 2}},  {"inc", {0x6, 1}},
    {"isz", {0x7, 2}},  {"add", {0x8, 1}},  {"ld", {0xA, 1}},   {"xch", {0xB, 1}},
    {"bbl", {0xC, 1}},  {"ldm", {0xD, 1}},  {"clb", {0xF0, 0}}, {"clc", {0xF1, 0}},
    {"iac", {0xF2, 0}}, {"cmc", {0xF3, 0}}, {"cma", {0xF4, 0}}, {"ral", {0xF5, 0}},
    {"rar", {0xF6, 0}}, {"tcc", {0xF7, 0}}, {"dac", {0xF8, 0}}, {"tcs", {0xF9, 0}},
    {"stc", {0xFA, 0}}, {"daa", {0xFB, 0}}, {"kbp", {0xFC, 0}}, {"dcl", {0xFD, 0}},
};

std::vector<uint8_t> Codegen::generate() {
    for (auto& inst : instArray_) {
        opcodeData opcodeData = opcodeTable[inst.opcode];
        code_.push_back(opcodeData.opcode);
        for (size_t i = 0; i < opcodeData.operandCount; i++) {
            code_.push_back(inst.value[i]);
        }
    }

    return code_;
}
