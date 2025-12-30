#include "lexer.h"
#include <cstdint>
#include <string>

int main(int32_t argc, char *argv[]) {
  std::string code = R"(ldm 10;
        xch r0;
        ldm 3;
        add r0;)";

  Lexer lexer(code);
  auto lexems = lexer.tokenize();
}
