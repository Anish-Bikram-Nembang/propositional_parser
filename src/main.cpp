#include "compare.hpp"
#include "evaluator.hpp"
#include "lexer.hpp"
#include "postfix.hpp"
#include "CLI/CLI.hpp"
#include "truthTableGenerator.hpp"
#include "varNamesCollector.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

  auto compare =
      app.add_subcommand("compare", "Compare two propositions for equivalence");
  string propositionToCompare1, propositionToCompare2;

  compare->add_option("first", propositionToCompare1)->required();
  compare->add_option("second", propositionToCompare2)->required();

  CLI11_PARSE(app, argc, argv);
  try {
    if (*print) {
      vector<Token> lexedProposition = lex(propositionToPrint);
      vector<Token> postfixedProposition = producePostfix(lexedProposition);
      vector<string> variables = collectVarNames(postfixedProposition);
      generateTruthTable(postfixedProposition, variables, propositionToPrint);
    }
    if (*compare) {
      vector<Token> lexedProposition1 = lex(propositionToCompare1);
      vector<Token> postfixedProposition1 = producePostfix(lexedProposition1);

      vector<Token> lexedProposition2 = lex(propositionToCompare2);
      vector<Token> postfixedProposition2 = producePostfix(lexedProposition2);

      vector<string> variablesOfProposition1 =
          collectVarNames(postfixedProposition1);
      vector<string> variablesOfProposition2 =
          collectVarNames(postfixedProposition2);

      std::unordered_set<std::string> seen(variablesOfProposition1.begin(),
                                           variablesOfProposition1.end());

      std::vector<std::string> variables = variablesOfProposition1;
      for (const std::string &variable : variablesOfProposition2) {
        if (seen.insert(variable).second) {
          variables.push_back(variable);
        }
      }
      bool result =
          areEqual(postfixedProposition1, postfixedProposition2, variables);
      if (result)
        cout << "The two propositions are equivalent\n";
      else
        cout << "The two propositions are not equivalent\n";
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
