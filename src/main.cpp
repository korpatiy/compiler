#include <iostream>
#include <memory>
#include "models/analyzer/headers/Token.h"
#include "models/io/headers/Error.h"

int main() {
  auto token = make_unique<ConstantToken>(23);
  auto constant = token->getConstant();
  auto value = constant->toString();

  auto error = make_unique<Error>(1, 25, 3);
  error->showError();

  auto error1 = make_unique<Error>(2, 34, 5);
  error1->showError();

  return 0;
}
