#pragma once

#include "parser.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

struct opcodeData {
    uint8_t opcode;
    uint8_t operandCount;
};

extern std::unordered_map<std::string, opcodeData> opcodeTable;

class Codegen {
    std::vector<Instruction> instArray_;
    std::vector<uint8_t> code_;

  public:
    Codegen(std::vector<Instruction> instArray) : instArray_(std::move(instArray)) {}
    std::vector<uint8_t> generate();
};
