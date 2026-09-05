#include "./core.hpp"
#include "stdexcept"
#include <stdexcept>
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
bool isTokenBoundary(const char &c) {
  return c == '&' || c == '|' || c == '!' || c == '-' || c == '<' || c == '(' ||
         c == ')';
}
bool notAValidChar(const char &c) {
  return !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') || c == '_');
}
bool isANumber(const char &c) { return c >= '0' && c <= '9'; }

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

  string strippedProposition = stripWhitespaces(proposition);

  std::vector<Token> lexedProposition{};
  size_t length = strippedProposition.length();
  while (!strippedProposition.empty()) {
    bool operatorFoundorEOL{false};
    for (size_t i = 0; !operatorFoundorEOL && i < strippedProposition.length();
         i++) {
      if (strippedProposition[i] == '&') {
        lexedProposition.push_back(Token{Type::OPERATOR, Operator::AND});
        operatorFoundorEOL = true;
        strippedProposition = strippedProposition.substr(1);
      } else if (strippedProposition[i] == '|') {
        lexedProposition.push_back(Token{Type::OPERATOR, Operator::OR});
        operatorFoundorEOL = true;
        strippedProposition = strippedProposition.substr(1);
      } else if (strippedProposition[i] == '(') {
        lexedProposition.push_back(Token{Type::LPAREN});
        operatorFoundorEOL = true;
        strippedProposition = strippedProposition.substr(1);
      } else if (strippedProposition[i] == ')') {
        lexedProposition.push_back(Token{Type::RPAREN});
        operatorFoundorEOL = true;
        strippedProposition = strippedProposition.substr(1);
      } else if (strippedProposition[i] == '!') {
        lexedProposition.push_back(Token{Type::OPERATOR, Operator::NOT});
        operatorFoundorEOL = true;
        strippedProposition = strippedProposition.substr(1);
      } else if (strippedProposition[i] == '-') {
        if ((i + 1) >= strippedProposition.length()) {
          throw std::invalid_argument("invalid character at position " +
                                      to_string(i));
        }
        if (strippedProposition[i + 1] != '>') {
          throw std::invalid_argument("invalid character at position " +
                                      to_string(i));
        }

        lexedProposition.push_back(
            Token{Type::OPERATOR, Operator::IMPLICATION});
        operatorFoundorEOL = true;
        strippedProposition = strippedProposition.substr(2);
      } else if (strippedProposition[i] == '<') {
        if ((i + 2) >= strippedProposition.length()) {
          throw std::invalid_argument("invalid character at position " +
                                      to_string(i));
        }
        if (!(strippedProposition[i + 1] == '-' &&
              strippedProposition[i + 2] == '>')) {
          throw std::invalid_argument("invalid character at position " +
                                      to_string(i));
        }
        lexedProposition.push_back(
            Token{Type::OPERATOR, Operator::BICONDITIONAL});
        operatorFoundorEOL = true;
        strippedProposition = strippedProposition.substr(3);
      } else {
        string subStr{""};
        subStr.reserve(length);
        if (i < strippedProposition.length()) {
          size_t j = 0;
          if (isANumber(strippedProposition[j])) {
            throw std::invalid_argument(
                "Variable name cannot begin with a number");
          }
          while (j < strippedProposition.length() &&
                 !isTokenBoundary(strippedProposition[j])) {
            if (notAValidChar(strippedProposition[j])) {
              throw std::invalid_argument("Invalid character");
            }
            if (j < strippedProposition.length()) {
              subStr.append(1, strippedProposition[j]);
            }
            j++;
          }
          strippedProposition = strippedProposition.substr(subStr.length());
          operatorFoundorEOL = true;
          lexedProposition.push_back(Token{Type::VARIABLE, subStr});
        }
      }
    }
  }
  lexedProposition.push_back(Token{Type::END});
  return lexedProposition;
}
