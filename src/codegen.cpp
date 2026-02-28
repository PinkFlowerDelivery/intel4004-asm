#include "codegen.h"
#include "parser.h"
#include <cstdint>

std::unordered_map<std::string, opcodeInfo> opcodeTable = {
    {"nop", {0x00, false, 0}}, {"jcn", {0x1, false, 2}},  {"fim", {0x2, false, 2}},
    {"fin", {0x3, false, 2}},  {"jin", {0x3, false, 1}},  {"jun", {0x4, true, 1}},
    {"jms", {0x5, true, 1}},   {"inc", {0x6, false, 1}},  {"isz", {0x7, false, 2}},
    {"add", {0x8, false, 1}},  {"sub", {0x9, false, 1}},  {"ld", {0xA, false, 1}},
    {"xch", {0xB, false, 1}},  {"bbl", {0xC, false, 1}},  {"ldm", {0xD, false, 1}},
    {"clb", {0xF0, false, 0}}, {"clc", {0xF1, false, 0}}, {"iac", {0xF2, false, 0}},
    {"cmc", {0xF3, false, 0}}, {"cma", {0xF4, false, 0}}, {"ral", {0xF5, false, 0}},
    {"rar", {0xF6, false, 0}}, {"tcc", {0xF7, false, 0}}, {"dac", {0xF8, false, 0}},
    {"tcs", {0xF9, false, 0}}, {"stc", {0xFA, false, 0}}, {"daa", {0xFB, false, 0}},
    {"kbp", {0xFC, false, 0}}, {"dcl", {0xFD, false, 0}}, {"store", {0xFE, false, 2}}};

std::vector<uint8_t> Codegen::generate() {
    code_.clear();

    for (const auto& instr : instArray_) {
        opcodeInfo opInfo = opcodeTable.at(instr.opcode);

        if (opInfo.isLabel) {
            code_.push_back((opInfo.opcode << 4) | instr.value[0]);
            code_.push_back(instr.value[1]);
            continue;
        }

        switch (opInfo.argSize) {
        case 0: {
            code_.push_back(opInfo.opcode);
            continue;
        }
        case 1: {
            code_.push_back((opInfo.opcode << 4) | instr.value[0]);
            continue;
        }
        case 2: {
            code_.push_back((opInfo.opcode << 4) | instr.value[0]);
            code_.push_back(instr.value[1]);
            continue;
        }
        }
    }

    return code_;
}
