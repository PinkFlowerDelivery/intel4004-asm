#include "parser.h"
#include "fmt/base.h"
#include "fmt/format.h"
#include "tokens.h"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <variant>
#include <vector>

std::unordered_map<std::string, InstructionMeta> mapOfInstructionMeta = {
    {"nop", {0, {}, 1}},         {"jun", {1, {LABEL}, 2}},    {"dec", {1, {REGISTER}, 1}},
    {"add", {1, {REGISTER}, 1}}, {"sub", {1, {REGISTER}, 1}}, {"ld", {1, {REGISTER}, 1}},
    {"xch", {1, {REGISTER}, 1}}, {"ldm", {1, {INTEGER}, 1}},  {"clc", {0, {}, 1}},
    {"stc", {0, {}, 1}},
};

std::vector<Instruction> Parser::parse() {
    collectLabels();

    for (size_t i = 0; i < lexems_.size(); i++) {
        if (std::holds_alternative<Asm4004::Identifier>(lexems_[i])) {
            parseInstruction(i);
        }
    }

    return instructions_;
}

void Parser::parseInstruction(size_t& i) {
    Instruction rawInst;
    Asm4004::Identifier ident = std::get<Asm4004::Identifier>(lexems_[i]);
    InstructionMeta instMeta = mapOfInstructionMeta[ident.name];

    if (mapOfInstructionMeta.find(ident.name) == mapOfInstructionMeta.end()) {
        throw std::runtime_error(fmt::format("Unexpected identifactor: {}", ident.name));
    }

    rawInst.opcode = ident.name;

    parseInstructionArgs(i, rawInst, instMeta);

    instructions_.push_back(rawInst);
};

void Parser::collectLabels() {
    size_t pc = 0;
    for (size_t i = 0; i < lexems_.size(); i++) {
        if (std::holds_alternative<Asm4004::Label>(lexems_[i])) {
            std::string labelName = std::get<Asm4004::Label>(lexems_[i]).name;
            tableOfLabels_[labelName] = pc;
            continue;
        }
        if (std::holds_alternative<Asm4004::Identifier>(lexems_[i])) {
            std::string identName = std::get<Asm4004::Identifier>(lexems_[i]).name;
            if (mapOfInstructionMeta.find(identName) == mapOfInstructionMeta.end()) {
                throw std::runtime_error(fmt::format("Unexpected identifier: {}", identName));
            }

            InstructionMeta meta = mapOfInstructionMeta[identName];

            i += meta.operandCount;
            pc += meta.byteSize;
        }
    }
};

void Parser::parseInstructionArgs(size_t& i, Instruction& rawInstruction,
                                  InstructionMeta& instructionMeta) {
    for (size_t j = 0; j < instructionMeta.operandCount; j++) {
        i++;

        // If an instruction takes two operands
        if (j == 1) {
            if (!std::holds_alternative<Asm4004::Comma>(lexems_[i])) {
                throw std::runtime_error("Expected ',' between operands");
            }
            i++;
        }

        if (instructionMeta.operandTypes[j] == INTEGER &&
            std::holds_alternative<Asm4004::Integer>(lexems_[i])) {
            rawInstruction.value[j] = std::get<Asm4004::Integer>(lexems_[i]).value;
            continue;
        }

        if (instructionMeta.operandTypes[j] == REGISTER &&
            std::holds_alternative<Asm4004::Identifier>(lexems_[i])) {
            std::string rawRegister = std::get<Asm4004::Identifier>(lexems_[i]).name;

            rawInstruction.value[j] = registerToNumber(rawRegister);

            continue;
        }

        if (instructionMeta.operandTypes[j] == LABEL &&
            std::holds_alternative<Asm4004::Identifier>(lexems_[i])) {
            std::string labelName = std::get<Asm4004::Identifier>(lexems_[i]).name;

            if (tableOfLabels_.find(labelName) == tableOfLabels_.end()) {
                throw std::runtime_error(fmt::format("Undefined label: {}", labelName));
            }

            ssize_t labelAddr = tableOfLabels_[labelName];

            rawInstruction.value[0] = (labelAddr >> 8) & 0x0F;
            rawInstruction.value[1] = labelAddr & 0xFF;

            continue;
        }

        throw std::runtime_error(fmt::format("Unexpected arg"));
    }
};

uint8_t Parser::registerToNumber(const std::string& reg) {
    if (reg.size() < 2 || reg[0] != 'r') {
        throw std::runtime_error(fmt::format("Unexpected argument: {}", reg));
    }
    return static_cast<uint8_t>(std::stoi(reg.substr(1)));
};
