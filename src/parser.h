#pragma once

#include "tokens.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

struct Instruction
{
    std::array<uint8_t, 2> value = {0};
    std::string opcode;
};

enum OperandType
{
    NONE,
    INTEGER,
    REGISTER,
    LABEL
};
struct InstructionMeta
{
    uint8_t operandCount;
    std::array<OperandType, 2> operandTypes;
};

extern std::unordered_map<std::string, InstructionMeta> mapOfInstuctionMeta;

class Parser
{
  public:
    std::vector<Asm4004::Token> lexems_;
    std::vector<Instruction> instructions_;
    std::unordered_map<std::string, uint16_t> tableOfLabels_;

    static uint8_t registerToNumber(const std::string& reg);
    void parseInstruction(size_t& i);
    void parseInstructionArgs(size_t& i, Instruction& rawInstruction,
                              InstructionMeta& instructionMeta);
    void parseLabel(size_t& i);

  public:
    Parser(std::vector<Asm4004::Token>& lexems) : lexems_(lexems) {};
    std::vector<Instruction> parse();
};
