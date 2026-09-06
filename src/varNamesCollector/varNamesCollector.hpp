#include "../lexer/lexer.hpp"
#include <unordered_set>

std::unordered_set<std::string> collectVarNames(std::vector<Token> tokens);
