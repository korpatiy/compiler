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
  Identifier(const string &_name, EIdentClass ident_class, shared_ptr<Type> _type);
  basic_string<char> getName();
  shared_ptr<Type> getType();
};

#endif //COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_IDENTIFIER_H_
