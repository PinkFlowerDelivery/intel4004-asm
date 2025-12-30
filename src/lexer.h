#pragma once

#include "tokens.h"
#include <string>
#include <unordered_map>
#include <vector>

class Lexer {
  std::string rawCode_;
  std::vector<Asm4004::Token> lexemBuffer_;

public:
  Lexer(std::string &rawCode) : rawCode_(rawCode) {};
  std::vector<Asm4004::Token> tokenize();
  void rawIdentiferToTokenType();
};
