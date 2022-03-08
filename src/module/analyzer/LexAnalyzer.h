#ifndef COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#define COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#include "../io/IOModule.h"
#include <string>
#include <memory>
using namespace std;

class LexAnalyzer {
 private:
  unique_ptr<IOModule> ioModule;
 public:
  explicit LexAnalyzer(const string &_filePath);
  ~LexAnalyzer() = default;
  /** Сканирует следующий токен */
  void scanNextToken();
};

#endif //COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
