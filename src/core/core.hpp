#pragma once
#include "string"
#include "variant"

using namespace std;
enum class Operator { AND, OR, IMPLICATION, BICONDITIONAL, NOT };
enum class Type { OPERATOR, VARIABLE, LPAREN, RPAREN, END };

using ShapeData = variant<monostate, Operator, string>;

int getOperatorPrecedence(Operator op);

struct Token {
  Type type;
  ShapeData data;
  Token(Type t, ShapeData d) : type{t}, data{d} {}
};
