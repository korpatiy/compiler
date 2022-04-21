#include "SemAnalyzer.h"

#include <utility>

SemAnalyzer::SemAnalyzer(shared_ptr<IOModule> _ioModule) {
  ioModule = std::move(_ioModule);
}

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

void SemAnalyzer::analyzeAssigment(EType _varType, EType _exprType) {
  if (_varType == UNKNOWN_TYPE || _varType == _exprType
      || (_varType == REAL_TYPE && (_exprType == REAL_TYPE || _exprType == INT_TYPE))
      || (_varType == STRING_TYPE && _exprType == STRING_TYPE)) {
    return;
  }
  /* несоответствие типов */
  ioModule->logError(401, 1);
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

shared_ptr<Type> SemAnalyzer::findType(const shared_ptr<Scope> &_findScope, const string &_identName) {
  auto ident = _findScope->lookupIdent(_identName);

  if (ident != nullptr && ident->getIdentClass() != CONST_CLASS)
    return ident->getType();

  auto parentScope = _findScope->getParentScope();
  if (parentScope != nullptr)
    return findType(parentScope, _identName);

  return nullptr;
}

void SemAnalyzer::findDuplicateOrAddIdentifier(const string &_identName, const shared_ptr<Identifier> &_identifier) {
  if (scope->lookupIdent(_identName) != nullptr)
    /* имя описано повторно */
    ioModule->logError(101, 2);
  else
    scope->addIdentifier(_identifier);
}

shared_ptr<Type> SemAnalyzer::analyzeRelations(EType _type1, EType _type2) {
  if ((_type1 == INT_TYPE || _type1 == REAL_TYPE)
      && (_type2 == INT_TYPE || _type2 == REAL_TYPE)) {
    return shared_ptr<BooleanType>();
  }
  return nullptr;
}

shared_ptr<Type> SemAnalyzer::analyzeAdditive(EType _type1, EType _type2, TokenCode _operation, int _tokenSize) {
  /* Проверка аддитивных операторов */
  if (_operation == TokenCode::plus || _operation == TokenCode::minus) {
    auto type = analyzeNumericTypes(_type1, _type2);
    if (type != nullptr)
      return type;
    ioModule->logError(211, _tokenSize);
  }

  /* проверка опертора orSy */
  if (_operation == orSy) {
    if (_type1 == BOOLEAN_TYPE && _type2 == BOOLEAN_TYPE)
      return make_shared<BooleanType>();
    /* операнды AND, NOT, OR должны быть булевыми */
    ioModule->logError(210, _tokenSize);
  }
  return nullptr;
}

shared_ptr<Type> SemAnalyzer::analyzeMultiplicative(EType _type1,
                                                    EType _type2,
                                                    TokenCode _operation,
                                                    int _tokenSize) {
  /* Проверка оперторов div, mod */
  if (_operation == divSy || _operation == modSy) {
    if (_type1 == INT_TYPE && _type2 == INT_TYPE)
      return make_shared<IntType>();
    /* операнды DIV и MOD должны быть целыми */
    ioModule->logError(212);
  }

  /* Проверка оперторов /, * */
  if (_operation == slash || _operation == star) {
    auto type = analyzeNumericTypes(_type1, _type2);
    if (type != nullptr)
      return type;

    /* недопустимые типы операндов в операции "/" */
    if (_operation == slash) ioModule->logError(214);
    /* недопустимые типы операндов в операции "*" */
    if (_operation == star) ioModule->logError(213);
  }

  /* Проверка опертора andSy, * */
  if (_operation == andSy) {
    if (_type1 == BOOLEAN_TYPE && _type2 == BOOLEAN_TYPE)
      return make_shared<BooleanType>();
    /* операнды AND, NOT, OR должны быть булевыми */
    ioModule->logError(210, _tokenSize);
  }

  return nullptr;
}

shared_ptr<Type> SemAnalyzer::analyzeNumericTypes(EType _type1, EType _type2) {
  if ((_type1 == INT_TYPE || _type1 == REAL_TYPE)
      && (_type2 == INT_TYPE || _type2 == REAL_TYPE)) {
    auto returnedType = _type1 == REAL_TYPE ? REAL_TYPE : _type2 == REAL_TYPE ? REAL_TYPE : INT_TYPE;
    if (returnedType == INT_TYPE)
      return make_shared<IntType>();
    else return make_shared<RealType>();
  }
  return nullptr;
}

void SemAnalyzer::checkRightTerm(const shared_ptr<struct Type> &_type) {
  if (_type == nullptr || _type->getTypeName() == INT_TYPE || _type->getTypeName() == REAL_TYPE)
    ioModule->logError(211);
}