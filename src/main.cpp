#include "codegen.h"
#include "lexer.h"
#include "parser.h"
#include <cstdint>
#include <fmt/base.h>
#include <fstream>
#include <sstream>
#include <string>

std::string readCode(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main(int32_t argc, char* argv[]) {
    std::string input;
    std::string output = "main.bin";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-o") {
            if (i + 1 >= argc) {
                fmt::println(stderr, "error: -o requires filename");
                return 1;
            }
            output = argv[++i];
        } else {
            if (input.empty()) {
                input = arg;
            } else {
                fmt::println(stderr, "error: unexpected argument: {}", arg);
                return 1;
            }
        }
    }

    if (input.empty()) {
        fmt::println(stderr, "usage: i4004asm input.asm [-o output.bin]");
        return 1;
    }

    std::string code = readCode(input);

    Lexer lexer(code);
    auto lexems = lexer.tokenize();

    Parser parser{lexems};
    auto instructions = parser.parse();

    Codegen codegen(instructions);
    std::vector<uint8_t> outCode = codegen.generate();

    for (auto d : outCode) {
        fmt::print("{:x} ", d);
    }

    std::ofstream out(output, std::ios::binary);
    out.write(reinterpret_cast<const char*>(outCode.data()), outCode.size());
    out.close();
}
