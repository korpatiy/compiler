#ifndef COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_
#define COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_

#include "memory"
#include "string"
#include "../../../models/analyzer/semantic/Scope.h"

using namespace std;

/**
 * Модуль семантического анализтора
 */
class SemAnalyzer {
 private:
  shared_ptr<Scope> currentScope;

 public:
  SemAnalyzer();
  ~SemAnalyzer() = default;

  shared_ptr<Scope> openScope();

};

#endif //COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_
