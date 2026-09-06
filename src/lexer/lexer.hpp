#pragma once
#include <string>
#include <variant>
#include <vector>

using namespace std;
enum class Operator { AND, OR, IMPLICATION, BICONDITIONAL, NOT };
enum class Type { OPERATOR, VARIABLE, LPAREN, RPAREN, UNKNOWN };
using ShapeData = variant<monostate, Operator, string>;

struct Token {
  Type type;
  ShapeData data;
  Token(Type t, ShapeData d = std::monostate{}) : type{t}, data{d} {}
};
std::vector<Token> lex(string proposition);
