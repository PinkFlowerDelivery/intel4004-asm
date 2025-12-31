#pragma once

#include "tokens.h"
#include <cstdint>

struct Instuction {
  Asm4004::TokenType opcode;
  uint8_t value;
};

class Parser {
  void parse();
};
