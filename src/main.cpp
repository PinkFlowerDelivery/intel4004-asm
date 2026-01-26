#include "lexer.h"
#include "parser.h"
#include <cstdint>
#include <fmt/base.h>
#include <string>

int main(int32_t argc, char* argv[]) {
    std::string code = R"(
    label: ldm 10
    xch r1 
    ldm 2 
    add r1
    jun label
  )";

    Lexer lexer(code);
    auto lexems = lexer.tokenize();

    Parser parser{lexems};
    auto instructions = parser.parse();

    for (const auto& instr : parser.instructions_) {
        fmt::println("Opcode: {}, Value: {:02X} {:02X}", instr.opcode, instr.value[0],
                     instr.value[1]);
    }

    for (const auto& [label, addr] : parser.tableOfLabels_) {
        fmt::println("{} -> {}", label, addr);
    }
}
