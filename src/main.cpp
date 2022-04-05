#include <memory>
#include <Windows.h>
#include "models/io/headers/Error.h"
#include "module/io/IOModule.h"
#include "module/analyzer/lexer/LexAnalyzer.h"
#include "module/analyzer/synaxer/SyntaxAnalyzer.h"

int main() {
  //Windows
  SetConsoleOutputCP(CP_UTF8);
  setlocale(LC_ALL, "Russian");

  auto analyzer = make_unique<SyntaxAnalyzer>("C:/Users/Slava/Desktop/compiler/src/hello.txt");
  analyzer->start();

  return 0;
}
