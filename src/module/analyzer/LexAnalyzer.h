#ifndef COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#define COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#include <string>
using namespace std;

class LexAnalyzer {

 public:
  ~LexAnalyzer() = default;
  /** //todo in lexanalyzer branch */
  void scanSymbol(const string& symbol);
};

#endif //COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
