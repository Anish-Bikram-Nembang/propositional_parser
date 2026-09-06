#include "./lexer/lexer.hpp"
#include "./postfixProducer/postfix.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
  string proposition;
  cout << "Enter a proposition:" << '\n';
  getline(cin, proposition);
  cout << "The proposition you entered is: \n" << proposition << '\n';

  vector<Token> lexedProposition = lex(proposition);
  vector<Token> postfixProposition = producePostfix(lexedProposition);

  return 0;
}
