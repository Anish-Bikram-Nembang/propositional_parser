#include "./core.hpp"
#include "stdexcept"
#include <string>
#include <vector>

int getOperatorPrecedence(Operator op) {
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
    throw std::invalid_argument("unhandled Operator in getOperatorPrecedence");
  }
}

string stripWhitespaces(const string &str) {
  string strippedString{""};
  size_t length = str.length();
  strippedString.reserve(length);
  for (size_t i = 0; i < length; i++) {
    if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
      strippedString.append(1, str[i]);
    }
  }
  return strippedString;
}
std::vector<Token> lexer(string proposition) {
  string andIdentifier = "&";
  string orIdentifier = "|";
  string notIdentifier = "!";

  string strippedProposition = stripWhitespaces(proposition);

  std::vector<Token> lexedProposition{};
  size_t length = strippedProposition.length();
  while (!strippedProposition.empty()) {
    string subStr{""};
    size_t countOfIndexTraversed{0};
    subStr.reserve(length);
    bool operatorFound{false};
    for (size_t i = 0; !operatorFound; i++) {
      if (strippedProposition[i] == '&') {
        lexedProposition.push_back(Token{Type::OPERATOR, Operator::AND});
        operatorFound = true;
        countOfIndexTraversed++;
      } else if (strippedProposition[i] == '|') {
        lexedProposition.push_back(Token{Type::OPERATOR, Operator::OR});
        operatorFound = true;
        countOfIndexTraversed++;
      } else if (strippedProposition[i] == '!') {
        lexedProposition.push_back(Token{Type::OPERATOR, Operator::NOT});
        operatorFound = true;
        countOfIndexTraversed++;
      } else if (strippedProposition[i] == '-' &&
                 strippedProposition[i + 1] == '>') {
        lexedProposition.push_back(
            Token{Type::OPERATOR, Operator::IMPLICATION});
        operatorFound = true;
        countOfIndexTraversed = 2;
      } else if (strippedProposition[i] == '<' &&
                 strippedProposition[i + 1] == '-' &&
                 strippedProposition[i + 2] == '>') {
        lexedProposition.push_back(
            Token{Type::OPERATOR, Operator::BICONDITIONAL});
        operatorFound = true;
        countOfIndexTraversed = 3;
      } else {
      }
      strippedProposition =
          strippedProposition.substr(0, countOfIndexTraversed);
    }
  }
  return lexedProposition;
}
