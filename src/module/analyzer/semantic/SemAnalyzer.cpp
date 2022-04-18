#include "SemAnalyzer.h"

SemAnalyzer::SemAnalyzer() = default;

void SemAnalyzer::openScope() {
  auto newScope = make_shared<Scope>(scope);
  scope = newScope;
}

void SemAnalyzer::initTypes() {
  scope->addIdentifier(
      make_shared<Identifier>("integer", TYPE_CLASS, make_unique<IntType>())
  );
  scope->addIdentifier(
      make_shared<Identifier>("real", TYPE_CLASS, make_unique<RealType>())
  );
  scope->addIdentifier(
      make_shared<Identifier>("string", TYPE_CLASS, make_unique<StringType>())
  );
  scope->addIdentifier(
      make_shared<Identifier>("boolean", TYPE_CLASS, make_unique<BooleanType>())
  );
}

shared_ptr<Scope> SemAnalyzer::getLocalScope() {
  return scope;
}

shared_ptr<Identifier> SemAnalyzer::findIdentifier(const shared_ptr<Scope> &_findScope, const string &_identName) {
  auto ident = _findScope->lookupIdent(_identName);
  if (ident != nullptr)
    return ident;
  auto parentScope = _findScope->getParentScope();
  if (parentScope != nullptr)
    return findIdentifier(parentScope, _identName);
  return nullptr;
}
