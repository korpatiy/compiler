#include <memory>
#include <Windows.h>
#include "models/io/headers/Error.h"
#include "module/io/IOModule.h"

int main() {
  //Windows
  SetConsoleOutputCP(CP_UTF8);
  setlocale(LC_ALL, "Russian");

  IOModule io = IOModule();
  io.scan("C:/Users/Slava/Desktop/compiler/src/hello.txt");
  vector<Error> errors = io.getErrors();


  if (!errors.empty()) {
    for (Error error : errors) {
      cout << error.showError() << "\n";
    }
  }

  /*auto token = make_unique<ConstantToken>(23);
  auto constant = token->getConstant();
  auto value = constant->toString();

  auto error = make_unique<Error>(1, 25, 3);
  error->showError();

  auto error1 = make_unique<Error>(2, 34, 5);
  error1->showError();*/
  return 0;
}
