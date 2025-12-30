#include "tokens.h"

std::unordered_map<std::string, Asm4004::TokenType> Asm4004::mapOfTokens = {
    // Registers
    {"r0", Asm4004::TokenType::R0},
    {"r1", Asm4004::TokenType::R1},
    {"r2", Asm4004::TokenType::R2},
    {"r3", Asm4004::TokenType::R3},
    {"r4", Asm4004::TokenType::R4},
    {"r5", Asm4004::TokenType::R5},
    {"r6", Asm4004::TokenType::R6},
    {"r7", Asm4004::TokenType::R7},
    {"r8", Asm4004::TokenType::R8},
    {"r9", Asm4004::TokenType::R9},
    {"r10", Asm4004::TokenType::R10},
    {"r11", Asm4004::TokenType::R11},
    {"r12", Asm4004::TokenType::R12},
    {"r13", Asm4004::TokenType::R13},
    {"r14", Asm4004::TokenType::R14},
    {"r15", Asm4004::TokenType::R15},

    // Instructions
    {"nop", Asm4004::TokenType::NOP},
    {"jun", Asm4004::TokenType::JUN},
    {"dec", Asm4004::TokenType::DEC},
    {"add", Asm4004::TokenType::ADD},
    {"sub", Asm4004::TokenType::SUB},
    {"ld", Asm4004::TokenType::LD},
    {"xch", Asm4004::TokenType::XCH},
    {"ldm", Asm4004::TokenType::LDM},
    {"clc", Asm4004::TokenType::CLC},
    {"stc", Asm4004::TokenType::STC}};
