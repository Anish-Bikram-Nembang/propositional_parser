#include "./lexer.hpp"
#include <stdexcept>
#include <string>
#include <vector>

bool isValidChar(const char &c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
         (c >= '0' && c <= '9') || c == '_';
}
bool isANumber(const char &c) { return c >= '0' && c <= '9'; }
void flushCurrentIdentifier(std::vector<Token> &tokenBuffer,
                            string &currentIdentifier) {
  if (currentIdentifier.length() != 0) {
    tokenBuffer.push_back(Token{Type::VARIABLE, currentIdentifier});
    currentIdentifier.clear();
  }
}
std::vector<Token> lex(const string &proposition) {
  std::vector<Token> lexedProposition{};
  string subStr{""};
  size_t cursor = 0;

  while (cursor < proposition.length()) {
    char c = proposition[cursor];
    if (c == ' ' || c == '\t' || c == '\n') {
      flushCurrentIdentifier(lexedProposition, subStr);
      cursor++;
      continue;
    } else if (c == '&') {
      flushCurrentIdentifier(lexedProposition, subStr);
      lexedProposition.push_back(Token{Type::OPERATOR, Operator::AND});
      cursor++;
    } else if (c == '|') {
      flushCurrentIdentifier(lexedProposition, subStr);
      lexedProposition.push_back(Token{Type::OPERATOR, Operator::OR});
      cursor++;
    } else if (c == '(') {
      flushCurrentIdentifier(lexedProposition, subStr);
      lexedProposition.push_back(Token{Type::LPAREN});
      cursor++;
    } else if (c == ')') {
      flushCurrentIdentifier(lexedProposition, subStr);
      lexedProposition.push_back(Token{Type::RPAREN});
      cursor++;
    } else if (c == '!') {
      flushCurrentIdentifier(lexedProposition, subStr);
      lexedProposition.push_back(Token{Type::OPERATOR, Operator::NOT});
      cursor++;
    } else if (c == '-') {
      flushCurrentIdentifier(lexedProposition, subStr);
      if ((cursor + 1) >= proposition.length()) {
        throw std::invalid_argument("invalid character at position " +
                                    to_string(cursor));
      }
      if (proposition[cursor + 1] != '>') {
        throw std::invalid_argument("invalid character at position " +
                                    to_string(cursor));
      }

      lexedProposition.push_back(Token{Type::OPERATOR, Operator::IMPLICATION});
      cursor += 2;
    } else if (c == '<') {
      flushCurrentIdentifier(lexedProposition, subStr);
      if ((cursor + 2) >= proposition.length()) {
        throw std::invalid_argument("invalid character at position " +
                                    to_string(cursor));
      }
      if (!(proposition[cursor + 1] == '-' && proposition[cursor + 2] == '>')) {
        throw std::invalid_argument("invalid character at position " +
                                    to_string(cursor));
      }
      lexedProposition.push_back(
          Token{Type::OPERATOR, Operator::BICONDITIONAL});
      cursor += 3;
    } else {
      if (subStr.length() == 0 && isANumber(c)) {
        throw std::invalid_argument("Variable name cannot begin with a number");
      }
      if (!isValidChar(c)) {
        throw std::invalid_argument("Invalid character");
      }
      subStr.append(1, c);
      cursor++;
    }
  }
  flushCurrentIdentifier(lexedProposition, subStr);
  lexedProposition.push_back(Token{Type::END});
  return lexedProposition;
}
