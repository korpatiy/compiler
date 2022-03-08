#include <memory>
#include <Windows.h>
#include "models/io/headers/Error.h"
#include "module/io/IOModule.h"
#include "module/analyzer/LexAnalyzer.h"

int main() {
  //Windows
  SetConsoleOutputCP(CP_UTF8);
  setlocale(LC_ALL, "Russian");

  auto analyzer = make_unique<LexAnalyzer>("C:/Users/Slava/Desktop/compiler/src/hello.txt");
  analyzer->scanNextToken();
  /*auto token = make_unique<ConstantToken>(23);
  auto constant = token->getConstant();
  auto value = constant->toString();

  auto error = make_unique<Error>(1, 25, 3);
  error->showError();

  auto error1 = make_unique<Error>(2, 34, 5);
  error1->showError();*/
  return 0;
}
