#include "./varNamesCollector.hpp"
#include <stdexcept>
#include <unordered_set>

std::vector<std::string> collectVarNames(const std::vector<Token> &tokens) {
  std::vector<std::string> varNames{};
  std::unordered_set<std::string> seen{};
  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == Type::VARIABLE) {
      const auto *var = std::get_if<std::string>(&tokens[i].data);
      if (!var) {
        throw std::invalid_argument("invalid var while collecting var names");
      }
      if (seen.find(*var) == seen.end()) {
        varNames.push_back(*var);
        seen.insert(*var);
      }
    }
  }
  return varNames;
}
