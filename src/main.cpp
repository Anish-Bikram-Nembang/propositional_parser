#include "./evaluator/evaluator.hpp"
#include "./lexer/lexer.hpp"
#include "./postfixProducer/postfix.hpp"
#include "CLI/CLI.hpp"
#include "truthTableGenerator/truthTableGenerator.hpp"
#include "varNamesCollector/varNamesCollector.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  CLI::App app{"a propositional parser"};

  app.require_subcommand(1);

  auto print = app.add_subcommand("print", "Print the truth table");
  string propositionToPrint;
  print->add_option("proposition", propositionToPrint,
                    "proposition to display truth table of");
  CLI11_PARSE(app, argc, argv);
  if (*print) {
    vector<Token> lexedProposition = lex(propositionToPrint);
    vector<Token> postfixedProposition = producePostfix(lexedProposition);
    vector<string> variables = collectVarNames(postfixedProposition);
    generateTruthTable(postfixedProposition, variables, propositionToPrint);
  }
  return 0;
}
