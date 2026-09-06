#pragma once
#include "../lexer/lexer.hpp"
#include <unordered_map>

bool eval(const vector<Token> &postfix,
          const std::unordered_map<std::string, bool> &variableValues);
