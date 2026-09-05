#include "./parser.hpp"
#include <stdexcept>
#include <unordered_map>
#include <variant>
std::unordered_map<Operator, vector<size_t>>
findIndexOfSeparation(const vector<Token> &tokens);
unique_ptr<AbstractSyntaxTree> parse(vector<Token> tokens) {
  std::unordered_map<Operator, vector<size_t>> operatorsMap =
      findIndexOfSeparation(tokens);
  if (tokens[0].type != Type::VARIABLE && tokens[0].type != Type::LPAREN) {
    throw std::invalid_argument("First element is not valid");
  }
}
std::unordered_map<Operator, vector<size_t>>
findIndexOfSeparation(const vector<Token> &tokens) {
  std::unordered_map<Operator, vector<size_t>> operators{};
  for (size_t i = 0; i < tokens.size(); i++) {
    if (const auto *op = std::get_if<Operator>(&tokens[i].data)) {
      operators[*op].push_back(i);
    }
  }
  return operators;
}
