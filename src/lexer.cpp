#include "lexer.h"
#include "tokens.h"
#include <cctype>
#include <cstdint>
#include <fmt/format.h>
#include <string>
#include <sys/types.h>

std::vector<Asm4004::Token> Lexer::tokenize() {
  uint32_t line = 0;
  std::string buffer;

  for (ssize_t i = 0; i < rawCode_.size(); i++) {
    switch (rawCode_[i]) {
    case ' ':
      break;

    case ',':
      lexemBuffer_.push_back(Asm4004::Comma{});
      break;
    case ':':
      lexemBuffer_.push_back(Asm4004::Colon{});
      break;
    case ';':
      lexemBuffer_.push_back(Asm4004::Semicolon{});
      break;

    default:

      if (std::isalpha(rawCode_[i]) || std::isdigit(rawCode_[i])) {
        while (std::isalpha(rawCode_[i]) || std::isdigit(rawCode_[i])) {
          buffer.push_back(rawCode_[i]);
          i++;
        }

        lexemBuffer_.push_back(
            Asm4004::Identifier{Asm4004::mapOfTokens[buffer]});
        buffer.clear();

        i--;
        break;
      }

      if (std::isdigit(rawCode_[i])) {

        while (std::isdigit(rawCode_[i])) {
          buffer.push_back(rawCode_[i]);
          i++;
        }

        lexemBuffer_.push_back(
            Asm4004::Integer{static_cast<uint8_t>(std::stoi(buffer))});

        buffer.clear();

        i--;
        break;
      }

      throw std::runtime_error(fmt::format("Error at line {}", line));

    case '\r':
      break;
    case '\t':
      break;
    case '\n':
      line++;
      break;
    }
  }

  return lexemBuffer_;
};
