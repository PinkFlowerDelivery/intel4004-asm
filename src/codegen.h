#pragma once

#include "parser.h"
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

struct opcodeInfo {
    uint8_t opcode;
    bool isLabel;
    uint8_t argSize;
};

extern std::unordered_map<std::string, opcodeInfo> opcodeTable;

class Codegen {
    std::vector<Instruction> instArray_;
    std::vector<uint8_t> code_;

  public:
    Codegen(std::vector<Instruction> instArray) : instArray_(std::move(instArray)) {}
    std::vector<uint8_t> generate();
};
