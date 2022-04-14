#ifndef COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_IDENTIFIER_H_
#define COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_IDENTIFIER_H_

#include "string"
#include "memory"
#include "Type.h"
using namespace std;

/**
 * Способ использования
 */
enum EIdentClass {
  PROG_CLASS = 300,
  TYPE_CLASS = 301,
  CONST_CLASS = 302,
  VAR_CLASS = 303,
};

/**
 * Идентификатор
 */
class Identifier {
 private:
  string identName;
  EIdentClass identClass;
  shared_ptr<Type> type;
 public:
  //Identifier(string& _idenName, );
};

#endif //COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_IDENTIFIER_H_
