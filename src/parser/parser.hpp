#include "../lexer/lexer.hpp"
#include <memory>
#include <vector>

struct Node {
  Type type;
  ShapeData data;
  unique_ptr<Node> leftChild;
  unique_ptr<Node> rightChild;
};
struct AbstractSyntaxTree {
  unique_ptr<Node> root;
};

unique_ptr<AbstractSyntaxTree> parse(vector<Token> tokens);
