#pragma once
#include "../lexer/lexer.hpp"

void generateTruthTable(const std::vector<Token> &postfix,
                        const std::vector<std::string> &variables,
                        const std::string &proposition);
