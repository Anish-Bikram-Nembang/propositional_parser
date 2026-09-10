#pragma once
#include "lexer.hpp"
#include <unordered_map>

bool eval(const std::vector<Token> &postfix,
          const std::unordered_map<std::string, bool> &variableValues);
