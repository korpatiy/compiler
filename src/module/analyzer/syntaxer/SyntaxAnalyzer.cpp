#include "SyntaxAnalyzer.h"
#include "../../../models/codes/Blocks.h"

SyntaxAnalyzer::SyntaxAnalyzer(const string &_filePath) {
  lexer = make_unique<LexAnalyzer>(_filePath);
  semancer = make_unique<SemAnalyzer>(lexer->getIOModule());
}

void SyntaxAnalyzer::accept(TokenCode tokenCode) {
  if (currentToken->getCode() == tokenCode)
    scanNextToken();
  else {
    int offset = currentToken->toString().size();
    if (currentToken->getCode() == endOfFile && tokenCode == point) offset = 0;
    lexer->getIOModule()->logError(tokenCode, offset);
  }
}

void SyntaxAnalyzer::scanNextToken() {
  currentToken = lexer->scanNextToken();
}

void SyntaxAnalyzer::skipTo(const set<enum TokenCode> &block) {
  while (block.count(currentToken->getCode()) != 1) {
    scanNextToken();
    if (currentToken->getCode() == endOfFile)
      break;
  }
}

bool SyntaxAnalyzer::isSymbolBelongTo(const set<TokenCode> &block) {
  return block.count(currentToken->getCode()) == 1;
}

void SyntaxAnalyzer::isBelongOrSkipTo(const set<enum TokenCode> &block, int errorCode) {
  if (!isSymbolBelongTo(block)) {
    lexer->getIOModule()->logError(errorCode);
    skipTo(block);
  }
}

set<TokenCode> SyntaxAnalyzer::unionOf(const set<TokenCode> &first, const set<TokenCode> &second) {
  set<TokenCode> res = first;
  res.insert(second.begin(), second.end());
  return res;
}

set<TokenCode> SyntaxAnalyzer::unionOf(TokenCode code, const set<TokenCode> &block) {
  set<TokenCode> res = block;
  res.insert(code);
  return res;
}

void SyntaxAnalyzer::program() {
  /* Открываем область */
  semancer->openScope();
  semancer->initTypes();

  scanNextToken();
  accept(programSy);
  accept(ident);
  accept(semicolon);
  descriptionSection();
  operatorSection();
  accept(point);
}

void SyntaxAnalyzer::descriptionSection() {
  auto descriptionSet = descriptionBlockSet;
  descriptionSet.insert(beginSy);
  /* Если нет раздела описаний, то идем дальше */
  isBelongOrSkipTo(descriptionSet, 18);
  if (currentToken->getCode() == beginSy) return;

  /* Есть раздел описаний */
  if (isSymbolBelongTo(descriptionBlockSet)) {
    /* Константы */
    isBelongOrSkipTo(descriptionSet, 18);
    descriptionSet.erase(constSy);
    if (currentToken->getCode() == constSy)
      constBlock();

    /* Типы */
    isBelongOrSkipTo(descriptionSet, 18);
    descriptionSet.erase(typeSy);
    if (currentToken->getCode() == typeSy)
      typeBlock();

    /* Переменные */
    isBelongOrSkipTo(descriptionSet, 18);
    descriptionSet.erase(varSy);
    if (currentToken->getCode() == varSy)
      varBlock();
  }
}

void SyntaxAnalyzer::constBlock() {
  accept(constSy);
  do {
    constDescription();
    accept(semicolon);
  } while (currentToken->getCode() == ident);
}

void SyntaxAnalyzer::constDescription() {
  if (currentToken->getCode() == ident) {
    string identName = currentToken->toString();
    accept(ident);
    accept(TokenCode::equal);
    auto constType = constRecognition(baseTypeCodeSet);

    auto identifier = make_shared<Identifier>(identName, CONST_CLASS, constType);

    semancer->findDuplicateOrAddIdentifier(identName, identifier);
  }
}

shared_ptr<Type> SyntaxAnalyzer::constRecognition(const set<enum TokenCode> &followBlock) {
  shared_ptr<Type> constType = nullptr;

  auto constSet = unionOf(ident, baseTypeCodeSet);
  auto constWithAdd = unionOf(constSet, additiveCodeSet);
  isBelongOrSkipTo(unionOf(constWithAdd, followBlock), 18);

  if (isSymbolBelongTo(constWithAdd)) {
    switch (currentToken->getCode()) {
      case intConst:
        constType = make_shared<IntType>();
        accept(intConst);
        break;
      case realConst:
        constType = make_shared<RealType>();
        accept(realConst);
        break;
      case stringConst:
        constType = make_shared<StringType>();
        accept(stringConst);
        break;
      case booleanConst:
        constType = make_shared<BooleanType>();
        accept(booleanConst);
        break;
      case ident: {
        constType = getIdent()->getType();
        accept(ident);
        break;
      }
      default:
        if (isSymbolBelongTo(additiveCodeSet)) {
          scanNextToken();
          switch (currentToken->getCode()) {
            case intConst:
              constType = make_shared<IntType>();
              break;
            case realConst:
              constType = make_shared<RealType>();
              break;
            case ident:
              constType = getIdent()->getType();
              break;
            default:
              break;
          }
          scanNextToken();
        }
        break;
    }
  }

  return constType;
}

shared_ptr<Identifier> SyntaxAnalyzer::getIdent() {
  string identName = currentToken->toString();
  auto identifier = semancer->findIdentifier(semancer->getLocalScope(), identName);
  if (identifier == nullptr) {
    /* имя не описано */
    lexer->getIOModule()->logError(14, identName.size());
    identifier = make_shared<Identifier>(identName, VAR_CLASS, move(make_shared<Type>(UNKNOWN_TYPE)));
    semancer->getLocalScope()->addIdentifier(identifier);
  }
  return identifier;
}

void SyntaxAnalyzer::typeBlock() {
  accept(typeSy);
  do {
    typeDescription();
    accept(semicolon);
  } while (currentToken->getCode() == ident);
}

void SyntaxAnalyzer::typeDescription() {
  if (currentToken->getCode() == ident) {
    string identName = currentToken->toString();
    accept(ident);
    accept(TokenCode::equal);
    auto type = typeRecognition();
    auto identifier = make_shared<Identifier>(identName, TYPE_CLASS, type);
    semancer->findDuplicateOrAddIdentifier(identName, identifier);
  }
}

void SyntaxAnalyzer::varBlock() {
  accept(varSy);
  do {
    varDescription();
    accept(semicolon);
  } while (currentToken->getCode() == ident);
}

void SyntaxAnalyzer::varDescription() {
  isBelongOrSkipTo(unionOf(ident, finishCodeSet), 2);
  if (currentToken->getCode() == ident) {
    vector<shared_ptr<Identifier>> variables;
    string identName = currentToken->toString();
    auto identifier = make_shared<Identifier>(identName, VAR_CLASS, nullptr);
    variables.push_back(identifier);

    accept(ident);
    while (currentToken->getCode() == comma) {
      accept(comma);
      identName = currentToken->toString();
      identifier = make_shared<Identifier>(identName, VAR_CLASS, nullptr);
      variables.push_back(identifier);
      accept(ident);
    }
    accept(colon);
    auto kek = currentToken->toString();
    auto varType = typeRecognition();

    for (const auto &ident: variables) {
      ident->setType(varType);
      semancer->findDuplicateOrAddIdentifier(ident->getName(), ident);
    }
  }
}

shared_ptr<Type> SyntaxAnalyzer::typeRecognition() {
  auto set = baseTypeCodeSet;
  set.insert(arrow);
  set.insert(ident);
  isBelongOrSkipTo(set, 10);
  shared_ptr<Type> type = nullptr;
  if (isSymbolBelongTo(set)) {
    if (currentToken->getCode() == arrow) {
      type = referenceType();
    } else
      type = simpleType();
  }
  return type;
}

shared_ptr<Type> SyntaxAnalyzer::referenceType() {
  shared_ptr<Type> type = nullptr;
  accept(arrow);
  string identName = currentToken->toString();
  type = semancer->findType(semancer->getLocalScope(), identName);
  if (type == nullptr)
    getIdent();
  accept(ident);
  return type;
}

shared_ptr<Type> SyntaxAnalyzer::simpleType() {
  shared_ptr<Type> type = nullptr;
  if (currentToken->getCode() == ident) {
    string identName = currentToken->toString();
    type = semancer->findType(semancer->getLocalScope(), identName);
    if (type == nullptr)
      getIdent();
    accept(ident);
  }
  return type;
}

void SyntaxAnalyzer::operatorSection() {
  auto point = set<TokenCode>{TokenCode::point};
  compoundOperator(point);
}

void SyntaxAnalyzer::operatorRecognition(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(operatorCodeSet, followBlock), 22);
  if (isSymbolBelongTo(operatorCodeSet)) {
    switch (currentToken->getCode()) {
      case ident:
        assigmentOperator(followBlock);
        break;
      case beginSy:
        compoundOperator(followBlock);
        break;
      case ifSy:
        ifOperator(followBlock);
        break;
      case whileSy:
        whileOperator(followBlock);
        break;
      case caseSy:
        caseOperator(followBlock);
        break;
      default:
        break;
    }
  }
}

void SyntaxAnalyzer::compoundOperator(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(beginSy, followBlock), 22);
  if (currentToken->getCode() == beginSy) {
    accept(beginSy);
    while (isSymbolBelongTo(operatorCodeSet)) {
      operatorRecognition(unionOf(finishCodeSet, followBlock));
      accept(semicolon);
    }
    accept(endSy);
  }
}

void SyntaxAnalyzer::assigmentOperator(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(ident, followBlock), 22);
  if (currentToken->getCode() == ident) {
    string identName = currentToken->toString();
    auto varType = variable(unionOf(assign, followBlock));

    accept(assign);

    auto exprType = expression(followBlock);
    semancer->analyzeAssigment(varType->getTypeName(), exprType->getTypeName());
  }
}

void SyntaxAnalyzer::ifOperator(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(ifSy, followBlock), 22);
  if (currentToken->getCode() == ifSy) {
    accept(ifSy);
    auto thenSet = unionOf(thenSy, followBlock);
    auto type = expression(thenSet);
    if (type == nullptr)
      lexer->getIOModule()->logError(401);

    accept(thenSy);
    auto elseSet = unionOf(elseSy, followBlock);
    operatorRecognition(elseSet);
    if (currentToken->getCode() == elseSy) {
      accept(elseSy);
      operatorRecognition(elseSet);
    }
  }
}

void SyntaxAnalyzer::whileOperator(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(whileSy, followBlock), 22);
  if (currentToken->getCode() == whileSy) {
    accept(whileSy);
    auto type = expression(unionOf(doSy, followBlock));
    if (type == nullptr)
      lexer->getIOModule()->logError(401);
    accept(doSy);
    operatorRecognition(followBlock);
  }
}

void SyntaxAnalyzer::caseOperator(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(caseSy, followBlock), 22);
  if (currentToken->getCode() == caseSy) {
    accept(caseSy);

    /* case of */
    auto type = expression(unionOf(ofSy, followBlock));
    if (type == nullptr)
      lexer->getIOModule()->logError(401);
    accept(ofSy);

    /* case end */
    auto endCaseSet = unionOf(endSy, followBlock);
    caseVariants(endCaseSet, type->getTypeName());

    /* Перебиарем варианты */
    while (currentToken->getCode() == semicolon) {
      accept(semicolon);
      caseVariants(endCaseSet, BOOLEAN_TYPE);
    }

    accept(endSy);
  }
}

void SyntaxAnalyzer::caseVariants(const set<enum TokenCode> &followBlock, EType followType) {
  isBelongOrSkipTo(unionOf(expressionWithAdditiveCodeSet, followBlock), 22);
  if (isSymbolBelongTo(expressionWithAdditiveCodeSet)) {
    auto type = constRecognition(unionOf(colon, followBlock));
    if (type == nullptr || type->getTypeName() != followType)
      lexer->getIOModule()->logError(401);
    /* Варианты через запятую */
    while (currentToken->getCode() == comma) {
      accept(comma);
      constRecognition(followBlock);
    }

    accept(colon);
    operatorRecognition(followBlock);
  }
}

shared_ptr<Type> SyntaxAnalyzer::variable(const set<enum TokenCode> &followBlock) {
  shared_ptr<Type> type = nullptr;
  isBelongOrSkipTo(unionOf(ident, followBlock), 22);
  if (currentToken->getCode() == ident) {
    auto identifier = getIdent();
    if (identifier->getIdentClass() == CONST_CLASS)
      lexer->getIOModule()->logError(400);
    type = identifier->getType();
    accept(ident);

    //todo ref
    if (currentToken->getCode() == arrow)
      accept(arrow);
  }
  return type;
}

shared_ptr<Type> SyntaxAnalyzer::expression(const set<enum TokenCode> &followBlock) {
  shared_ptr<Type> type = nullptr;
  auto exprSet = unionOf(leftPar, expressionWithAdditiveCodeSet);
  if (!isSymbolBelongTo(exprSet)) {
    lexer->getIOModule()->logError(23, currentToken->toString().size());
    skipTo(unionOf(exprSet, followBlock));
  }
  if (isSymbolBelongTo(exprSet)) {
    type = simpleExpression(unionOf(comparisonOperatorCodeSet, followBlock));

    /* Провяерем соответствие типов операторов */
    if (isSymbolBelongTo(comparisonOperatorCodeSet)) {
      scanNextToken();
      auto secondType = simpleExpression(followBlock);
      type = semancer->analyzeRelations(type->getTypeName(), secondType->getTypeName());
      if (type == nullptr)
        /* несоответствие типов для операции отношения */
        lexer->getIOModule()->logError(186);
    }
  }
  return type;
}

shared_ptr<Type> SyntaxAnalyzer::simpleExpression(const set<enum TokenCode> &followBlock) {
  shared_ptr<Type> type = nullptr;
  auto exprSet = unionOf(leftPar, expressionWithAdditiveCodeSet);
  isBelongOrSkipTo(unionOf(exprSet, followBlock), 22);
  if (isSymbolBelongTo(exprSet)) {
    bool isTermWithSign = false;

    /* Смотрим операции "+" и "-" */
    if (isSymbolBelongTo(additiveCodeSet)) {
      scanNextToken();
      isTermWithSign = true;
    }

    /* Добавляем оператор "or" */
    auto simpleExprWithOr = unionOf(orSy, additiveCodeSet);
    type = term(simpleExprWithOr);

    if (isTermWithSign)
      semancer->checkRightTerm(type);

    /* Провеярем аддитивные операции */
    while (isSymbolBelongTo(simpleExprWithOr)) {
      auto operation = currentToken->getCode();
      scanNextToken();
      auto secondType = term(simpleExprWithOr);
      type = semancer->analyzeAdditive(type->getTypeName(),
                                       secondType->getTypeName(),
                                       operation,
                                       static_cast<int>(currentToken->toString().size()));
    }
  }
  return type;
}

shared_ptr<Type> SyntaxAnalyzer::term(const set<enum TokenCode> &followBlock) {
  shared_ptr<Type> type = nullptr;
  auto termSet = unionOf(leftPar, expressionCodeSet);
  isBelongOrSkipTo(unionOf(termSet, followBlock), 22);
  if (isSymbolBelongTo(termSet)) {
    auto multiplicativeFollow = unionOf(multiplicativeCodeSet, followBlock);
    type = factor(multiplicativeFollow);

    /* Провеярем мультпликативные операции */
    while (isSymbolBelongTo(multiplicativeCodeSet)) {
      auto operation = currentToken->getCode();
      scanNextToken();
      auto secondType = factor(multiplicativeFollow);
      type = semancer->analyzeMultiplicative(type->getTypeName(),
                                             secondType->getTypeName(),
                                             operation,
                                             static_cast<int>(currentToken->toString().size()));
    }
  }
  return type;
}

shared_ptr<Type> SyntaxAnalyzer::factor(const set<enum TokenCode> &followBlock) {
  shared_ptr<Type> type = nullptr;
  auto factorSet = unionOf(leftPar, expressionCodeSet);
  isBelongOrSkipTo(unionOf(factorSet, followBlock), 22);
  if (isSymbolBelongTo(factorSet)) {
    switch (currentToken->getCode()) {
      case leftPar:
        accept(leftPar);
        type = expression(unionOf(rightPar, followBlock));
        accept(rightPar);
        break;
      case notSy:
        accept(notSy);
        type = factor(followBlock);
        if (type->getTypeName() != BOOLEAN_TYPE)
          /* операнды AND, NOT, OR должны быть булевыми */
          lexer->getIOModule()->logError(210);
        break;
      case intConst:
        type = make_shared<IntType>();
        accept(intConst);
        break;
      case realConst:
        type = make_shared<RealType>();
        accept(realConst);
        break;
      case stringConst:
        type = make_shared<StringType>();
        accept(stringConst);
        break;
      case ident: {
        string identName = currentToken->toString();
        auto identifier = semancer->findIdentifier(semancer->getLocalScope(), identName);
        if (identifier != nullptr) {
          switch (identifier->getIdentClass()) {
            case VAR_CLASS:
              type = variable(followBlock);
              break;
            case CONST_CLASS:
              type = identifier->getType();
              accept(ident);
            default:
              break;
          }
        } else {
          identifier = make_shared<Identifier>(identName, VAR_CLASS, make_unique<Type>(UNKNOWN_TYPE));
          semancer->findDuplicateOrAddIdentifier(identName, identifier);
          lexer->getIOModule()->logError(14);
          accept(ident);
        }
        break;
      }
      default:
        break;
    }
  }
  return type;
}

void SyntaxAnalyzer::start() {
  program();
}
