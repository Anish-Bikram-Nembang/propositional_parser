#include "./compare.hpp"
#include "../evaluator/evaluator.hpp"
#include <stdexcept>
#include <unordered_map>

bool areEqual(std::vector<Token> postfixedProposition1,
              std::vector<Token> postfixedProposition2,
              std::vector<std::string> variables) {
  if (variables.size() > 20) {
    throw std::invalid_argument("Number of variables in first and second "
                                "proposition combined cannot exceed 20");
  }
  std::unordered_map<std::string, bool> varValuesMap{};

  for (size_t assignment = 0; assignment < ((size_t)1 << variables.size());
       assignment++) {
    varValuesMap.clear();
    for (size_t i = 0; i < variables.size(); i++) {
      bool value = (assignment >> i) & 1;
      varValuesMap.insert({variables[i], value});
      size_t varWidth = variables[i].size();
    }
    bool result1 = eval(postfixedProposition1, varValuesMap);
    bool result2 = eval(postfixedProposition2, varValuesMap);

    if (result1 != result2)
      return false;
  }
  return true;
}
