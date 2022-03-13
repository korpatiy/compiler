#include <memory>
#include <Windows.h>
#include "models/io/headers/Error.h"
#include "module/io/IOModule.h"
#include "module/analyzer/LexAnalyzer.h"
#include "models/analyzer/headers/Token.h"
#include "models/codes/SymbolCodes.h"

int main() {
  //Windows
  SetConsoleOutputCP(CP_UTF8);
  setlocale(LC_ALL, "Russian");

  //auto analyzer = make_unique<LexAnalyzer>("C:/Users/Slava/Desktop/compiler/src/hello.txt");
  //analyzer->scanNextToken();

  return 0;
}
