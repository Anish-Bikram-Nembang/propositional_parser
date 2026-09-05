#include "iostream"
#include "string"

using namespace std;

/*
 * Operators
 *  ()
 *  !
 *  &
 *  |
 *  ->
 *  <->
 *  Binary tree
 *  - all internal vertices are operators and the leafs are variables
 */
enum Type { OPERATOR, VARIABLE };
struct Node {
  Type type;
  string identifier;
  Node *leftChild;
  Node *rightChild;
};
struct AST {
  Node root;
  int noOfVertices;
};
Node *parser(string proposition) {}
int main(void) {
  string proposition;
  cout << "Enter a proposition:" << '\n';
  getline(cin, proposition);
  cout << "The proposition you entered is: \n" << proposition << '\n';

  return 0;
}
