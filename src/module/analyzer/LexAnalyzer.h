#ifndef COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#define COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#include "../io/IOModule.h"
#include "../../models/analyzer/headers/Token.h"
#include <string>
#include <memory>
using namespace std;

class LexAnalyzer {
 private:
  unique_ptr<IOModule> ioModule;
  const int MAX_INT_SIZE = INT_MAX;
  //todo max string?
  const int MAX_STRING_SIZE = 255;

  unique_ptr<ConstantToken, default_delete<ConstantToken>> scanString();
  void scanNumber();

  void scanLater();
  void scanGreater();
  void scanColon();
  void scanPoint();
  void scanStar();
  void scanLeftPar();
  void scanFlPar();
  void scanFrPar();

 public:
  explicit LexAnalyzer(const string &_filePath);
  ~LexAnalyzer() = default;
  /** Сканирует следующий токен */
  unique_ptr<Token, default_delete<Token>> scanNextToken();
};

#endif //COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
