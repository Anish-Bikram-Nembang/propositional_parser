#include "./lexer/lexer.hpp"
#include "./postfixProducer/postfix.hpp"
#include "./varNamesCollector/varNamesCollector.hpp"
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main(void) {
  string proposition;
  cout << "Enter a proposition:" << '\n';
  getline(cin, proposition);
  cout << "The proposition you entered is: \n" << proposition << '\n';

  vector<Token> lexedProposition = lex(proposition);
  vector<Token> postfixProposition = producePostfix(lexedProposition);
  unordered_set<string> variables = collectVarNames(lexedProposition);

  return 0;
}
