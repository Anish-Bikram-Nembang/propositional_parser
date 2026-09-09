#include "./evaluator/evaluator.hpp"
#include "./lexer/lexer.hpp"
#include "./postfixProducer/postfix.hpp"
#include "CLI/CLI.hpp"
#include "truthTableGenerator/truthTableGenerator.hpp"
#include "varNamesCollector/varNamesCollector.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  CLI::App app{"a propositional parser"};
  app.require_subcommand(1);

  auto print = app.add_subcommand("print", "Print the truth table");
  string propositionToPrint;
  print
      ->add_option("proposition", propositionToPrint,
                   "proposition to display truth table of")
      ->required();

  auto evaluate = app.add_subcommand(
      "evaluate",
      "Evaluate a proposition with user entered values for the "
      "variables\n Allowed variable values are:\n T or t or true or True "
      "or 1 \n F or f or false or False or 0\n");
  string propositionToEvaluate;
  evaluate
      ->add_option("proposition", propositionToEvaluate,
                   "proposition to evaluate")
      ->required();
  CLI11_PARSE(app, argc, argv);
  try {
    if (*print) {
      vector<Token> lexedProposition = lex(propositionToPrint);
      vector<Token> postfixedProposition = producePostfix(lexedProposition);
      vector<string> variables = collectVarNames(postfixedProposition);
      generateTruthTable(postfixedProposition, variables, propositionToPrint);
    }
    if (*evaluate) {
      unordered_map<string, bool> variableWithValues{};
      vector<Token> lexedProposition = lex(propositionToEvaluate);
      vector<Token> postfixedProposition = producePostfix(lexedProposition);
      vector<string> variables = collectVarNames(postfixedProposition);

      for (const string &var : variables) {
        string variable;
        cout << "Enter value for " << var << " : ";
        cin >> variable;
        if (variable == "t" || variable == "T" || variable == "true" ||
            variable == "True" || variable == "1")
          variableWithValues.insert({var, true});
        else if (variable == "f" || variable == "F" || variable == "false" ||
                 variable == "False" || variable == "0")
          variableWithValues.insert({var, false});
        else
          throw invalid_argument("Invalid truth value for variable '" + var +
                                 "'");
      }
      cout << propositionToEvaluate << " = "
           << eval(postfixedProposition, variableWithValues) << "\n";
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
  return 0;
}
