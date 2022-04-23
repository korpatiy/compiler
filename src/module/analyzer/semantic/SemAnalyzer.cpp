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
  scope->addIdentifier(
      make_shared<Identifier>("true", CONST_CLASS, make_unique<BooleanType>())
  );
  scope->addIdentifier(
      make_shared<Identifier>("false", CONST_CLASS, make_unique<BooleanType>())
  );
}

shared_ptr<Scope> SemAnalyzer::getLocalScope() {
  return scope;
}

void SemAnalyzer::analyzeAssigment(const shared_ptr<Type> &_varType, const shared_ptr<Type> &_exprType) {
  if (_varType == nullptr || _exprType == nullptr) {
    /* несоответствие типов */
    ioModule->logError(401, 1);
    return;
  }

  auto varTypeName = _varType->getTypeName();
  auto varExprName = _exprType->getTypeName();
  /* Обработка ссылочного типа */
  varTypeName = analyzeRefType(_varType, varTypeName);
  varTypeName = analyzeRefType(_exprType, varExprName);

  if (varTypeName == UNKNOWN_TYPE || varTypeName == varExprName
      || (varTypeName == REAL_TYPE && (varExprName == REAL_TYPE || varExprName == INT_TYPE))
      || (varTypeName == STRING_TYPE && varExprName == STRING_TYPE)) {
    return;
  }
  /* несоответствие типов */
  ioModule->logError(401, 1);
}

EType SemAnalyzer::analyzeRefType(const shared_ptr<Type> &_varType, EType &varTypeName) const {
  if (varTypeName == REFERENCE_TYPE) {
    shared_ptr<ReferenceType> refType = (const shared_ptr<ReferenceType> &) (_varType);
    /* Смотрим тип указателя */
    varTypeName = refType->getRefType()->getTypeName();
  }
  return varTypeName;
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
    return make_shared<BooleanType>();
  }
  /* несоответствие типов для операции отношения */
  ioModule->logError(186);
  return nullptr;
}

shared_ptr<Type> SemAnalyzer::analyzeAdditive(const shared_ptr<Type> &_type1,
                                              const shared_ptr<Type> &_type2,
                                              TokenCode _operation,
                                              int _tokenSize) {
  /* Проверка аддитивных операторов */
  auto typeOne = _type1->getTypeName();
  auto typeTwo = _type2->getTypeName();
  typeOne = analyzeRefType(_type1, typeOne);
  typeTwo = analyzeRefType(_type2, typeTwo);
  if (_operation == TokenCode::plus || _operation == TokenCode::minus) {
    auto type = analyzeNumericTypes(typeOne, typeTwo);
    if (type != nullptr)
      return type;
    ioModule->logError(211, _tokenSize);
  }

  /* проверка опертора orSy */
  if (_operation == orSy) {
    if (typeOne == BOOLEAN_TYPE && typeTwo == BOOLEAN_TYPE)
      return make_shared<BooleanType>();
    /* операнды AND, NOT, OR должны быть булевыми */
    ioModule->logError(210, _tokenSize);
  }
  return nullptr;
}

shared_ptr<Type> SemAnalyzer::analyzeMultiplicative(shared_ptr<Type> _type1,
                                                    shared_ptr<Type> _type2,
                                                    TokenCode _operation,
                                                    int _tokenSize) {

  /* Проверка аддитивных операторов */
  auto typeOne = _type1->getTypeName();
  auto typeTwo = _type2->getTypeName();
  typeOne = analyzeRefType(_type1, typeOne);
  typeTwo = analyzeRefType(_type2, typeTwo);

  /* Проверка оперторов div, mod */
  if (_operation == divSy || _operation == modSy) {
    if (typeOne == INT_TYPE && typeTwo == INT_TYPE)
      return make_shared<IntType>();
    /* операнды DIV и MOD должны быть целыми */
    ioModule->logError(212);
  }

  /* Проверка оперторов /, * */
  if (_operation == slash || _operation == star) {
    auto type = analyzeNumericTypes(typeOne, typeTwo);
    if (type != nullptr)
      return type;

    /* недопустимые типы операндов в операции "/" */
    if (_operation == slash) ioModule->logError(214);
    /* недопустимые типы операндов в операции "*" */
    if (_operation == star) ioModule->logError(213);
  }

  /* Проверка опертора andSy, * */
  if (_operation == andSy) {
    if (typeOne == BOOLEAN_TYPE && typeTwo == BOOLEAN_TYPE)
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
  auto termType = _type->getTypeName();
  termType = analyzeRefType(_type, termType);
  if (_type == nullptr || termType == INT_TYPE || termType == REAL_TYPE)
    ioModule->logError(211);
}