#include "./truthTableGenerator.hpp"
#include "../evaluator/evaluator.hpp"
#include <iomanip>
#include <iostream>
#include <unordered_map>

void generateTruthTable(const std::vector<Token> &postfix,
                        const std::vector<std::string> &variables,
                        const std::string &proposition) {
  std::unordered_map<std::string, bool> varValuesMap{};
  size_t truthTableWidth{0};
  for (size_t assignment = 0; assignment < (1 << variables.size());
       assignment++) {
    varValuesMap.clear();
    for (size_t i = 0; i < variables.size(); i++) {
      if (i == 0 && assignment == 0) {
        for (size_t k = 0; k < variables.size(); k++) {
          std::cout << " " << variables[k] << " |";
          truthTableWidth += (variables[k].size() + 3);
        }
        std::cout << " " << proposition << "\n";
        truthTableWidth += (proposition.size() + 1);
        std::cout << std::setfill('-') << std::setw(truthTableWidth) << ""
                  << '\n';
        std::cout << std::setfill(' ');
      }
      bool value = (assignment >> i) & 1;
      varValuesMap.insert({variables[i], value});
      size_t varWidth = variables[i].size();
      std::cout << " " << std::setw(varWidth) << (value ? "T" : "F") << " |";
    }
    bool result = eval(postfix, varValuesMap);
    std::cout << " " << std::setw(proposition.size()) << (result ? "T" : "F")
              << '\n';
  }
}
