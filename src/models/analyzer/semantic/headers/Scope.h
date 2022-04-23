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
  /* Таблица идентификаторов */
  map<string, shared_ptr<Identifier>> identifiers;
  /* Внешняя по уровню область видимости */
  shared_ptr<Scope> parentScope;
 public:
  explicit Scope(shared_ptr<Scope> _scope);
  ~Scope() = default;

  /** Добавляет переданный идентификтаор [_ident] в таблицу */
  void addIdentifier(const shared_ptr<Identifier> &_ident);
  /** Возвращает идентификатор по имени */
  shared_ptr<Identifier> lookupIdent(const string &_identName);
  /** Возвращет объемлющую область */
  shared_ptr<Scope> getParentScope();
};

#endif //COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_SCOPE_H_
