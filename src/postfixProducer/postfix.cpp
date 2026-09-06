#include "./postfix.hpp"
#include <stack>
#include <stdexcept>
#include <variant>

bool shouldPop(const Operator &in, const Token &top);
bool isRightAssoc(const Operator &op) {
  return op == Operator::NOT || op == Operator::IMPLICATION;
}
int prec(const Operator &op);

vector<Token> producePostfix(const vector<Token> &tokens) {
  Type previousType{Type::UNKNOWN};
  vector<Token> outputList{};
  stack<Token> opStack{};
  if (tokens.empty()) {
    throw std::invalid_argument("Empty list of tokens");
  }
  if ((tokens[0].type != Type::LPAREN && tokens[0].type != Type::VARIABLE &&
       tokens[0].type != Type::OPERATOR) ||
      (tokens[tokens.size() - 1].type != Type::RPAREN &&
       tokens[tokens.size() - 1].type != Type::VARIABLE)) {
    throw std::invalid_argument("Invalid syntax");
  }
  if (tokens[0].type == Type::OPERATOR) {
    const Operator *op = std::get_if<Operator>(&tokens[0].data);
    if (op != nullptr) {
      if (*op != Operator::NOT) {
        throw std::invalid_argument(
            "proposition cannot start with a binary operator");
      }
    }
  }
  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == Type::VARIABLE) {
      if (previousType == Type::VARIABLE)
        throw std::invalid_argument(
            "Variable cannot be followed by a variable");
      if (previousType == Type::RPAREN)
        throw std::invalid_argument(
            "Right parenthesis cannot be followed by a variable");
      outputList.push_back(tokens[i]);
      previousType = Type::VARIABLE;
    } else if (tokens[i].type == Type::LPAREN) {
      if (previousType != Type::OPERATOR && previousType != Type::LPAREN &&
          previousType != Type::UNKNOWN) {
        throw std::invalid_argument("Only an operator or a left parenthesis "
                                    "can be followed by a left parenthesis");
      }
      opStack.push(tokens[i]);
      previousType = Type::LPAREN;
    } else if (tokens[i].type == Type::RPAREN) {
      if (previousType != Type::VARIABLE && previousType != Type::RPAREN) {
        throw std::invalid_argument("Only a variable or a right parenthesis "
                                    "can be followed by a right parenthesis");
      }
      while (!opStack.empty() && opStack.top().type != Type::LPAREN) {
        outputList.push_back(opStack.top());
        opStack.pop();
      }
      opStack.pop();
      previousType = Type::RPAREN;
    } else if (tokens[i].type == Type::OPERATOR) {
      Token tok = tokens[i];
      const Operator *op = std::get_if<Operator>(&tokens[i].data);
      if (previousType == Type::OPERATOR && *op != Operator::NOT) {
        throw std::invalid_argument(
            "A Binary operator cannot be followed by another operator");
      }
      if (previousType == Type::LPAREN && *op != Operator::NOT)
        throw std::invalid_argument(
            "A left parenthesis cannot be followed by a binary operator");
      while (opStack.size() != 0 && opStack.top().type == Type::OPERATOR &&
             shouldPop(*op, opStack.top())) {
        outputList.push_back(opStack.top());
        opStack.pop();
      }
      opStack.push(tok);
      previousType = Type::OPERATOR;
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
