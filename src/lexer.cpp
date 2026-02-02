#include "lexer.h"
#include "tokens.h"
#include <cctype>
#include <cstdint>
#include <fmt/format.h>
#include <string>
#include <sys/types.h>

std::vector<Asm4004::Token> Lexer::tokenize() {
    uint32_t line = 1;
    std::string buffer;

    while (i_ < rawCode_.size()) {
        switch (rawCode_[i_]) {
        case ' ':
        case '\r':
        case '\t':
            i_++;
            continue;

        case ',':
            lexemBuffer_.emplace_back(Asm4004::Comma{});
            i_++;
            continue;
        case '\n':
            line++;
            i_++;
            continue;
        case ';':
            skipComment();
            continue;

        default:

            if (std::isdigit(rawCode_[i_])) {
                parseInteger();
                continue;
            }

            if (std::isalpha(rawCode_[i_])) {
                parseIdentOrLabel();
                continue;
            }

            throw std::runtime_error(
                fmt::format("Unexpected symbol {} at line {}", rawCode_[i_], line));
        }
    }

    return lexemBuffer_;
};

void Lexer::parseInteger() {
    std::string buffer;
    while (i_ < rawCode_.size() && std::isdigit(rawCode_[i_])) {
        buffer.push_back(rawCode_[i_++]);
    }

    lexemBuffer_.emplace_back(Asm4004::Integer{std::stoi(buffer)});
};

void Lexer::parseIdentOrLabel() {

    std::string buffer;

    while (i_ < rawCode_.size() && std::isalnum(rawCode_[i_])) {
        buffer.push_back(rawCode_[i_++]);
    }

    if (i_ < rawCode_.size() && rawCode_[i_] == ':') {
        i_++;
        lexemBuffer_.emplace_back(Asm4004::Label{buffer});
    } else {
        lexemBuffer_.emplace_back(Asm4004::Identifier{buffer});
    }
};

void Lexer::skipComment() {
    while (rawCode_[i_] != '\n') {
        i_++;
    }
};
