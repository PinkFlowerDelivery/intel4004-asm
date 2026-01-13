#pragma once

#include <cstdint>
#include <string>
#include <variant>

namespace Asm4004
{

struct Identifier
{
    std::string name;
    bool operator==(const Identifier& other) const
    {
        return name == other.name;
    };
};
struct Integer
{
    int32_t value;
    bool operator==(const Integer& other) const
    {
        return value == other.value;
    };
};

struct HexadecimialInteger
{
    int32_t value;
    bool operator==(const Integer& other) const
    {
        return value == other.value;
    };
};

struct Label
{
    std::string name;
};

struct Comma
{
};

using Token = std::variant<Identifier, Comma, Integer, HexadecimialInteger, Label>;

} // namespace Asm4004
