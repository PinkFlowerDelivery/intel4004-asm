#include "parser.h"
#include "fmt/base.h"
#include "fmt/format.h"
#include "tokens.h"
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <variant>
#include <vector>

std::unordered_map<std::string, InstructionMeta> mapOfInstructionMeta = {
    {"nop", {0, {NONE}}},     {"jun", {1, {LABEL}}},    {"dec", {1, {REGISTER}}},
    {"add", {1, {REGISTER}}}, {"sub", {1, {REGISTER}}}, {"ld", {1, {REGISTER}}},
    {"xch", {1, {REGISTER}}}, {"ldm", {1, {INTEGER}}},  {"clc", {0, {NONE}}},
    {"stc", {0, {NONE}}},
};

std::vector<Instruction> Parser::parse()
{

    for (size_t i = 0; i < lexems_.size(); i++)
    {

        if (!std::holds_alternative<Asm4004::Identifier>(lexems_[i]))
        {
            continue;
        }

        std::string name = std::get<Asm4004::Identifier>(lexems_[i]).name;
        InstructionMeta meta = mapOfInstructionMeta[name];

        if (meta.operandTypes[0] == LABEL && i + 1 < lexems_.size() &&
            std::holds_alternative<Asm4004::Identifier>(lexems_[i + 1]))
        {
            std::string labelName = std::get<Asm4004::Identifier>(lexems_[i + 1]).name;
            tableOfLabels_[labelName] = i + 1;
        }
    }

    for (size_t i = 0; i < lexems_.size(); i++)
    {
        if (std::holds_alternative<Asm4004::Label>(lexems_[i]))
        {
            parseLabel(i);
            continue;
        }
        if (std::holds_alternative<Asm4004::Identifier>(lexems_[i]))
        {
            parseInstruction(i);
        }
    }

    return instructions_;
}

void Parser::parseInstruction(size_t& i)
{
    Instruction rawInst;
    Asm4004::Identifier ident = std::get<Asm4004::Identifier>(lexems_[i]);
    InstructionMeta instMeta = mapOfInstructionMeta[ident.name];

    if (mapOfInstructionMeta.find(ident.name) == mapOfInstructionMeta.end())
    {
        throw std::runtime_error(fmt::format("Unexpected identifactor: {}", ident.name));
    }

    rawInst.opcode = ident.name;

    parseInstructionArgs(i, rawInst, instMeta);

    instructions_.push_back(rawInst);
};

void Parser::parseLabel(size_t& i)
{
    Asm4004::Label label = std::get<Asm4004::Label>(lexems_[i]);
    tableOfLabels_[label.name] = i;
    i++;
};

void Parser::parseInstructionArgs(size_t& i, Instruction& rawInstruction,
                                  InstructionMeta& instructionMeta)
{
    for (size_t j = 0; j < instructionMeta.operandCount; j++)
    {
        i++;
        if (instructionMeta.operandTypes[j] == INTEGER &&
            std::holds_alternative<Asm4004::Integer>(lexems_[i]))
        {
            rawInstruction.value[j] = std::get<Asm4004::Integer>(lexems_[i]).value;
            continue;
        }

        if (instructionMeta.operandTypes[j] == REGISTER &&
            std::holds_alternative<Asm4004::Identifier>(lexems_[i]))
        {
            std::string rawRegister = std::get<Asm4004::Identifier>(lexems_[i]).name;

            rawInstruction.value[j] = registerToNumber(rawRegister);

            continue;
        }

        if (instructionMeta.operandTypes[j] == LABEL &&
            std::holds_alternative<Asm4004::Identifier>(lexems_[i]))
        {
            std::string labelName = std::get<Asm4004::Identifier>(lexems_[i]).name;
            ssize_t labelAddr = tableOfLabels_[labelName];

            rawInstruction.value[0] = (labelAddr >> 8) & 0x0F;
            rawInstruction.value[1] = labelAddr & 0xFF;

            continue;
        }

        throw std::runtime_error(fmt::format("Unexpected arg"));
    }
};

uint8_t Parser::registerToNumber(const std::string& reg)
{
    if (reg.size() < 2 || reg[0] != 'r')
    {
        throw std::runtime_error(fmt::format("Unexpected argument: {}", reg));
    }
    return static_cast<uint8_t>(std::stoi(reg.substr(1)));
};
