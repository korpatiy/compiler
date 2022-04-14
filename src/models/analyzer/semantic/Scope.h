#ifndef COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_SCOPE_H_
#define COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_SCOPE_H_

#include <map>
#include <vector>
#include <string>

#include "Identifier.h"
#include "Type.h"

using namespace std;

/**
 * Область видимости
 */
class Scope {
 private:
  map<string, Identifier> identifiers;
  vector<Type> types;
  shared_ptr<Scope> parentScope;
 public:
  Scope();
  ~Scope() = default;
};

#endif //COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_SCOPE_H_
