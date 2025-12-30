#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <variant>
namespace Asm4004 {

enum class TokenType {
  R0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  R15,

  // Instructions
  NOP,
  JUN,
  DEC,
  ADD,
  SUB,
  LD,
  XCH,
  LDM,
  CLC,
  STC
};

extern std::unordered_map<std::string, TokenType> mapOfTokens;

struct Identifier {
  TokenType name;
};

struct Comma {};
struct Colon {};
struct Semicolon {};
struct Integer {
  uint8_t value;
};

using Token = std::variant<Identifier, Comma, Colon, Integer, Semicolon>;

} // namespace Asm4004
