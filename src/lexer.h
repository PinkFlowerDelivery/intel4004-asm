#pragma once

#include "tokens.h"
#include <cstdio>
#include <string>
#include <vector>

class Lexer {
    std::string rawCode_;
    std::vector<Asm4004::Token> lexemBuffer_;
    ssize_t i_ = 0;

  public:
    Lexer(std::string& rawCode) : rawCode_(rawCode) {};
    void parseInteger();
    void parseIdentOrLabel();
    void skipComment();
    std::vector<Asm4004::Token> tokenize();
};
