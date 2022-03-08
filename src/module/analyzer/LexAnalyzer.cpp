#include "LexAnalyzer.h"

void LexAnalyzer::scanNextToken() {
  string symbol = ioModule->readNextSymbol();
  if (symbol.empty()) ioModule->readNextSymbol();
}

LexAnalyzer::LexAnalyzer(const string &_filePath) {
  ioModule = make_unique<IOModule>(_filePath);
}
