
int getOperatorPrecedence(Operator op) {
  switch (op) {
  case Operator::NOT:
    return 5;
  case Operator::AND:
    return 4;
  case Operator::OR:
    return 3;
  case Operator::IMPLICATION:
    return 2;
  case Operator::BICONDITIONAL:
    return 1;
  default:
    throw std::invalid_argument("unhandled Operator in getOperatorPrecedence");
  }
}
