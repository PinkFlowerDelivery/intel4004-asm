#pragma once

#include <cstdint>
#include <string>
#include <variant>

namespace Asm4004 {

struct Identifier {
    std::string name;

    bool operator==(const Identifier& other) const {
        return name == other.name;
    }
};
struct Integer {
    int32_t value;

    bool operator==(const Integer& other) const {
        return value == other.value;
    }
};

struct Label {
    std::string name;

    bool operator==(const Label& other) const {
        return name == other.name;
    }
};

struct Comma {
    bool operator==(const Comma& other) const {
        return true;
    }
};

using Token = std::variant<Identifier, Comma, Integer, Label>;

} // namespace Asm4004
