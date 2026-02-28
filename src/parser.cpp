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

std::unordered_map<std::string, InstructionMeta> tableInstrMeta = {
    {"nop", {0, {}, 1}},
    {"jcn", {2, {INTEGER, SLABEL}, 2}},
    {"fim", {2, {REGISTER, INTEGER}, 2}},
    {"fin", {1, {REGISTER}, 1}},
    {"jin", {1, {REGISTER}, 1}},
    {"jun", {1, {LABEL}, 2}},
    {"jms", {1, {LABEL}, 2}},
    {"inc", {1, {REGISTER}, 1}},
    {"isz", {2, {REGISTER, SLABEL}, 2}},
    {"add", {1, {REGISTER}, 1}},
    {"sub", {1, {REGISTER}, 1}},
    {"ld", {1, {REGISTER}, 1}},
    {"xch", {1, {REGISTER}, 1}},
    {"bbl", {1, {REGISTER}, 1}},
    {"dec", {1, {REGISTER}, 1}},
    {"ldm", {1, {INTEGER}, 1}},
    {"clb", {0, {}, 1}},
    {"clc", {0, {}, 1}},
    {"iac", {0, {}, 1}},
    {"cmc", {0, {}, 1}},
    {"cma", {0, {}, 1}},
    {"ral", {0, {}, 1}},
    {"rar", {0, {}, 1}},
    {"tcc", {0, {}, 1}},
    {"dac", {0, {}, 1}},
    {"tcs", {0, {}, 1}},
    {"stc", {0, {}, 1}},
    {"daa", {0, {}, 1}},
    {"kbp", {0, {}, 1}},
    {"dcl", {0, {}, 1}},
    // Custom instruction
    {"store", {2, {REGISTER, INTEGER}, 2}}};

bool Instruction::operator==(const Instruction& other) const {
    return value == other.value && opcode == other.opcode;
};

std::vector<Instruction> Parser::parse() {
    collectLabels();

    parseInstruction();

    return instructions_;
}

void Parser::parseInstruction() {

    for (size_t i = 0; i < lexems_.size(); i++) {
        if (std::holds_alternative<Asm4004::Identifier>(lexems_[i])) {
            Instruction rawInst;
            std::string ident = std::get<Asm4004::Identifier>(lexems_[i]).name;

            if (tableInstrMeta.find(ident) == tableInstrMeta.end()) {
                throw std::runtime_error(fmt::format("Unexpected identifactor: {}", ident));
            }

            InstructionMeta instMeta = tableInstrMeta[ident];

            rawInst.opcode = ident;

            parseInstructionArgs(i, rawInst, instMeta);

            instructions_.push_back(rawInst);
        }
    }
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

            if (tableInstrMeta.find(identName) == tableInstrMeta.end()) {
                continue;
            }

            InstructionMeta meta = tableInstrMeta[identName];

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

        if (instructionMeta.operandTypes[j] == SLABEL &&
            std::holds_alternative<Asm4004::Identifier>(lexems_[i])) {
            std::string labelName = std::get<Asm4004::Identifier>(lexems_[i]).name;

            if (tableOfLabels_.find(labelName) == tableOfLabels_.end()) {
                throw std::runtime_error(fmt::format("Undefined label: {}", labelName));
            }

            uint16_t labelAddr = tableOfLabels_[labelName];

            if (labelAddr > 255) {
                throw std::runtime_error(
                    fmt::format("Label {}: address too large for 8-bit field", labelName));
            }

            rawInstruction.value[j] = labelAddr;

            continue;
        }

        throw std::invalid_argument(fmt::format("Unexpected arg"));
    }
};

uint8_t Parser::registerToNumber(const std::string& reg) {
    if (reg.size() < 2 || reg[0] != 'r') {
        throw std::runtime_error(fmt::format("Unexpected argument: {}", reg));
    }
    return static_cast<uint8_t>(std::stoi(reg.substr(1)));
};
