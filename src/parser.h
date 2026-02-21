#pragma once

#include "tokens.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

struct Instruction {
    std::array<uint8_t, 2> value = {0};
    std::string opcode;

    bool operator==(const Instruction& other) const;
};

enum OperandType { INTEGER, REGISTER, LABEL, SLABEL };
struct InstructionMeta {
    uint8_t operandCount;
    std::array<OperandType, 2> operandTypes;
    uint8_t byteSize;
};

extern std::unordered_map<std::string, InstructionMeta> mapOfInstuctionMeta;

class Parser {
    std::vector<Asm4004::Token> lexems_;
    std::vector<Instruction> instructions_;
    std::unordered_map<std::string, uint16_t> tableOfLabels_;

    static uint8_t registerToNumber(const std::string& reg);
    void parseInstruction(size_t& i);
    void parseInstructionArgs(size_t& i, Instruction& rawInstruction,
                              InstructionMeta& instructionMeta);
    void collectLabels();

  public:
    Parser(std::vector<Asm4004::Token>& lexems) : lexems_(lexems) {};
    std::vector<Instruction> parse();
};
