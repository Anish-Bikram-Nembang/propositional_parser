#include "./lexer/lexer.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void parser(string proposition) {
  int noOfOpenParenthesis{0};
  int noOfCloseParenthesis{0};
  for (int i = 0; i < proposition.length(); i++) {
    if (proposition[i] == '(')
      noOfOpenParenthesis++;
    if (proposition[i] == ')')
      noOfCloseParenthesis++;
  }
  cout << "open: " << noOfOpenParenthesis << '\n';
  cout << "close: " << noOfCloseParenthesis << '\n';
}
int main(void) {
  string proposition;
  cout << "Enter a proposition:" << '\n';
  getline(cin, proposition);
  cout << "The proposition you entered is: \n" << proposition << '\n';
  vector<Token> lexedProposition = lex(proposition);
  return 0;
}
