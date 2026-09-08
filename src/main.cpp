#include "./evaluator/evaluator.hpp"
#include "./lexer/lexer.hpp"
#include "./postfixProducer/postfix.hpp"
#include "truthTableGenerator/truthTableGenerator.hpp"
#include "varNamesCollector/varNamesCollector.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main(void) {
  string proposition;
  int option;
  cout << "select an option: " << '\n'
       << "1. generate truth table 2.evaluate a specific expression path"
       << '\n';
  cin >> option;
  cin.ignore();
  switch (option) {
  case 1: {
    cout << "Enter a proposition:" << '\n';
    getline(cin, proposition);
    vector<Token> lexedProposition = lex(proposition);
    vector<Token> postfixProposition = producePostfix(lexedProposition);
    generateTruthTable(postfixProposition, collectVarNames(postfixProposition),
                       proposition);
    break;
  }
  case 2: {
    cout << "Enter a proposition:" << '\n';
    getline(cin, proposition);
    vector<Token> lexedProposition = lex(proposition);
    vector<Token> postfixProposition = producePostfix(lexedProposition);
    vector<string> vars = collectVarNames(postfixProposition);

    unordered_map<string, bool> varWithValues{};
    cout << "Allowed values are:  \n 1. for truth values : T or t or 1\n 2. "
            "for false values : F or f or 0\n";
    for (const string &var : vars) {
      string val{};
      cout << "Enter value for " << var << ": ";
      cin >> val;
      if (val == "1" || val == "t" || val == "T") {
        varWithValues.insert({var, true});
      } else if (val == "0" || val == "f" || val == "F") {
        varWithValues.insert({var, false});
      } else {
        throw invalid_argument("Invalid input");
      }
    }
    cout << proposition << " : " << eval(postfixProposition, varWithValues)
         << '\n';

    break;
  }
  case 3:
    break;
  default:
    break;
  }

  return 0;
}
