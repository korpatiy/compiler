#ifndef COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_
#define COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_

#include "memory"
#include "string"
#include "../../../models/analyzer/semantic/headers/Scope.h"

using namespace std;

/**
 * Модуль семантического анализтора
 */
class SemAnalyzer {
 private:
  shared_ptr<Scope> scope;

 public:
  SemAnalyzer();
  ~SemAnalyzer() = default;

  void openScope();
  void initTypes();

  shared_ptr<Scope> getLocalScope();
  shared_ptr<Identifier> findIdentifier(const shared_ptr<Scope> &_findScope, const string &_identName);
};

#endif //COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_
