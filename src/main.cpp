#include "codegen.h"
#include "lexer.h"
#include "parser.h"
#include <cstdint>
#include <fmt/base.h>
#include <fstream>
#include <string>

int main(int32_t argc, char* argv[]) {
    std::string code = R"(
    ldm 10
  )";

    Lexer lexer(code);
    auto lexems = lexer.tokenize();

    Parser parser{lexems};
    auto instructions = parser.parse();

    Codegen codegen(instructions);
    std::vector<uint8_t> outCode = codegen.generate();

    for (auto& d : outCode) {
        fmt::print("{} ", d);
    }

    std::ofstream out("out.bin", std::ios::binary);
    out.write(reinterpret_cast<const char*>(outCode.data()), outCode.size());
    out.close();
}
