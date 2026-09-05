#include "./postfix.hpp"
#include <stack>
#include <stdexcept>
#include <variant>

bool shouldPop(const Operator &in, const Token &top);
bool isRightAssoc(const Operator &op) {
  return op == Operator::NOT || op == Operator::IMPLICATION;
}
int prec(const Operator &op) {
  switch (op) {
  case Operator::NOT:
    return 5;
  case Operator::AND:
    return 4;
  case Operator::OR:
    return 3;
  case Operator::IMPLICATION:
    return 2;
  case Operator::BICONDITIONAL:
    return 1;
  default:
    throw std::invalid_argument("Invalid Operator");
  }
}

vector<Token> producePostfix(const vector<Token> &tokens) {
  vector<Token> outputList{};
  stack<Token> opStack{};
  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == Type::VARIABLE) {
      outputList.push_back(tokens[i]);
    } else if (tokens[i].type == Type::LPAREN) {
      opStack.push(tokens[i]);
    } else if (tokens[i].type == Type::RPAREN) {
      while (!opStack.empty() && opStack.top().type != Type::LPAREN) {
        outputList.push_back(opStack.top());
        opStack.pop();
      }
      opStack.pop();
    } else if (tokens[i].type == Type::OPERATOR) {
      Token tok = tokens[i];
      const Operator *op = std::get_if<Operator>(&tokens[i].data);
      while (opStack.size() != 0 && opStack.top().type == Type::OPERATOR &&
             shouldPop(*op, opStack.top())) {
        outputList.push_back(opStack.top());
        opStack.pop();
      }
      if (opStack.empty()) {
        throw std::invalid_argument("No left parenthesis found");
      }
      opStack.push(tok);
    }
  }
  while (opStack.size() != 0) {
    if (opStack.top().type == Type::LPAREN) {
      throw std::invalid_argument("No right parenthesis found");
    }
    outputList.push_back(opStack.top());
    opStack.pop();
  }
  return outputList;
}
bool shouldPop(const Operator &in, const Token &top) {
  if (top.type == Type::LPAREN)
    return false;
  auto *op = std::get_if<Operator>(&top.data);
  if (!op)
    return false;
  if (isRightAssoc(in))
    return prec(in) < prec(*op);
  return prec(in) <= prec(*op);
}
