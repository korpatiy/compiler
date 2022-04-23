#include "../headers/Scope.h"

#include <memory>

Scope::Scope(shared_ptr<Scope> _scope) {
  parentScope = std::move(_scope);
}

void Scope::addIdentifier(const shared_ptr<Identifier> &_ident) {
  string identName = _ident->getName();
  if (identifiers.count(identName) != 1) {
    identifiers[identName] = _ident;
  }
}

shared_ptr<Identifier> Scope::lookupIdent(const string &_identName) {
  if (identifiers.count(_identName) == 1) {
    return identifiers[_identName];
  }
  return nullptr;
}

shared_ptr<Scope> Scope::getParentScope() {
  return parentScope;
}
