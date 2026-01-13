#include "lexer.h"
#include "parser.h"
#include <cstdint>
#include <string>

int main(int32_t argc, char* argv[])
{
    std::string code = R"(
    ldm 10 
    xch r1 
    ldm 2  
    main: add r1 
    jun main
  )";

    Lexer lexer(code);
    auto lexems = lexer.tokenize();

    Parser parser{lexems};
    auto insructions = parser.parse();
}
