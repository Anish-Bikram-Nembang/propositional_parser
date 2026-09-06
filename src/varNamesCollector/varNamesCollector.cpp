#include "./varNamesCollector.hpp"
#include <stdexcept>
#include <unordered_set>

std::unordered_set<std::string>
collectVarNames(const std::vector<Token> &tokens) {
  std::unordered_set<std::string> varNames{};
  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == Type::VARIABLE) {
      const auto *var = std::get_if<std::string>(&tokens[i].data);
      if (!var) {
        throw std::invalid_argument("invalid var while collecting var names");
      }
      varNames.insert(*var);
    }
  }
  return varNames;
}
