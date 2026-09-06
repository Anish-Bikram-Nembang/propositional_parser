#include "./evaluator.hpp"
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>

bool AND(bool a, bool b) { return a && b; }
bool OR(bool a, bool b) { return a || b; }
bool NOT(bool a) { return !a; }
bool BICONDITIONAL(bool a, bool b) {
  return (a == true && b == true) || (a == false && b == false);
}
bool IMPLICATION(bool a, bool b) { return !(a == true && b == false); }

bool eval(const std::vector<Token> &postfix,
          const std::unordered_map<std::string, bool> &variableValues) {
  std::stack<bool> result;
  for (size_t i = 0; i < postfix.size(); i++) {
    if (postfix[i].type == Type::VARIABLE) {
      if (const auto *var = std::get_if<std::string>(&postfix[i].data))
        result.push(variableValues.at(*var));
      else
        throw std::invalid_argument("invalid variable in " + std::to_string(i) +
                                    "th element of postfix");
    } else if (postfix[i].type == Type::OPERATOR) {
      if (const auto *op = std::get_if<Operator>(&postfix[i].data)) {
        if (*op == Operator::NOT) {
          bool val = NOT(result.top());
          result.pop();
          result.push(val);
        } else {
          bool b = result.top();
          result.pop();
          bool a = result.top();
          result.pop();
          switch (*op) {
          case Operator::AND:
            result.push(AND(a, b));
            break;
          case Operator::OR:
            result.push(OR(a, b));
            break;
          case Operator::IMPLICATION:
            result.push(IMPLICATION(a, b));
            break;
          case Operator::BICONDITIONAL:
            result.push(BICONDITIONAL(a, b));
            break;
          default:
            throw std::invalid_argument("Error while evaluating the postfix");
          }
        }

      } else
        throw std::invalid_argument("invalid operator in " + std::to_string(i) +
                                    "th element of postfix");
    } else {
      throw std::invalid_argument("invalid token in " + std::to_string(i) +
                                  "th element of postfix");
    }
  }
  if (result.size() > 1)
    throw std::invalid_argument(
        "Error while evaluating the postfix; more than 1 bool result left");
  if (result.empty())
    throw std::invalid_argument(
        "Error while evaluating the postfix; no bool result left");
  return result.top();
}
