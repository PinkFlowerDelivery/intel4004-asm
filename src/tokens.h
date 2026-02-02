#pragma once

#include <cstdint>
#include <string>
#include <variant>

namespace Asm4004 {

struct Identifier {
    std::string name;
};
struct Integer {
    int32_t value;
};

struct Label {
    std::string name;
};

struct Comma {};

using Token = std::variant<Identifier, Comma, Integer, Label>;

} // namespace Asm4004
