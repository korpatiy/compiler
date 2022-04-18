#include "SyntaxAnalyzer.h"
#include "../../../models/codes/Blocks.h"

SyntaxAnalyzer::SyntaxAnalyzer(const string &_filePath) {
  lexer = make_unique<LexAnalyzer>(_filePath);
  semancer = make_unique<SemAnalyzer>();
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

    if (semancer->getLocalScope()->lookupIdent(identName) != nullptr)
      /* имя описано повторно */
      lexer->getIOModule()->logError(101, currentToken->toString().size());
    else
      semancer->getLocalScope()->addIdentifier(identifier);
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
        constType = getIdentType();
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
              constType = getIdentType();
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

shared_ptr<Type> SyntaxAnalyzer::getIdentType() {
  string identName = currentToken->toString();
  auto identifier = semancer->findIdentifier(semancer->getLocalScope(), identName);
  if (identifier == nullptr) {
    /* имя не описано */
    lexer->getIOModule()->logError(104);
    identifier = make_shared<Identifier>(identName, CONST_CLASS, move(make_shared<Type>(UNKNOWN_TYPE)));
    semancer->getLocalScope()->addIdentifier(identifier);
  }
  return identifier->getType();
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
    accept(ident);
    accept(TokenCode::equal);
    typeRecognition();

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
    accept(ident);
    while (currentToken->getCode() == comma) {
      accept(comma);
      accept(ident);
    }
    accept(colon);
    typeRecognition();
  }
}

void SyntaxAnalyzer::typeRecognition() {
  auto set = baseTypeCodeSet;
  set.insert(arrow);
  set.insert(ident);
  isBelongOrSkipTo(set, 10);

  if (currentToken->getCode() == arrow) {
    referenceType();
  } else
    simpleType();
}

void SyntaxAnalyzer::referenceType() {
  accept(arrow);
  accept(ident);
}

void SyntaxAnalyzer::simpleType() {
  accept(ident);
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
    variable(unionOf(assign, followBlock));
    accept(assign);
    expression(followBlock);
  }
}

void SyntaxAnalyzer::ifOperator(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(ifSy, followBlock), 22);
  if (currentToken->getCode() == ifSy) {
    accept(ifSy);
    auto thenSet = unionOf(thenSy, followBlock);
    expression(thenSet);
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
    expression(unionOf(doSy, followBlock));
    accept(doSy);
    operatorRecognition(followBlock);
  }
}

void SyntaxAnalyzer::caseOperator(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(caseSy, followBlock), 22);
  if (currentToken->getCode() == caseSy) {
    accept(caseSy);

    /* case of */
    expression(unionOf(ofSy, followBlock));
    accept(ofSy);

    /* case end */
    auto endCaseSet = unionOf(endSy, followBlock);
    caseVariants(endCaseSet);

    /* Перебиарем варианты */
    while (currentToken->getCode() == semicolon) {
      accept(semicolon);
      caseVariants(endCaseSet);
    }

    accept(endSy);
  }
}

void SyntaxAnalyzer::caseVariants(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(expressionWithAdditiveCodeSet, followBlock), 22);
  if (isSymbolBelongTo(expressionWithAdditiveCodeSet)) {
    constRecognition(unionOf(colon, followBlock));
    /* Варианты через запятую */
    while (currentToken->getCode() == comma) {
      accept(comma);
      constRecognition(followBlock);
    }

    accept(colon);
    operatorRecognition(followBlock);
  }
}

void SyntaxAnalyzer::variable(const set<enum TokenCode> &followBlock) {
  isBelongOrSkipTo(unionOf(ident, followBlock), 22);
  if (currentToken->getCode() == ident) {
    accept(ident);
    if (currentToken->getCode() == arrow)
      accept(arrow);
  }
}

void SyntaxAnalyzer::expression(const set<enum TokenCode> &followBlock) {
  auto exprSet = unionOf(leftPar, expressionWithAdditiveCodeSet);
  if (!isSymbolBelongTo(exprSet)) {
    lexer->getIOModule()->logError(23, currentToken->toString().size());
    skipTo(unionOf(exprSet, followBlock));
  }
  if (isSymbolBelongTo(exprSet)) {
    simpleExpression(unionOf(comparisonOperatorCodeSet, followBlock));

    if (isSymbolBelongTo(comparisonOperatorCodeSet)) {
      scanNextToken();
      simpleExpression(followBlock);
    }
  }
}

void SyntaxAnalyzer::simpleExpression(const set<enum TokenCode> &followBlock) {
  auto exprSet = unionOf(leftPar, expressionWithAdditiveCodeSet);
  isBelongOrSkipTo(unionOf(exprSet, followBlock), 22);
  if (isSymbolBelongTo(exprSet)) {
    /* Смотрим операции "+" и "-" */
    if (isSymbolBelongTo(additiveCodeSet))
      scanNextToken();

    /* Добавляем оператор "or" */
    auto simpleExprWithOr = unionOf(orSy, additiveCodeSet);
    term(simpleExprWithOr);

    while (isSymbolBelongTo(simpleExprWithOr)) {
      scanNextToken();
      term(simpleExprWithOr);
    }
  }
}

void SyntaxAnalyzer::term(const set<enum TokenCode> &followBlock) {
  auto termSet = unionOf(leftPar, expressionCodeSet);
  isBelongOrSkipTo(unionOf(termSet, followBlock), 22);
  if (isSymbolBelongTo(termSet)) {
    auto multiplicativeFollow = unionOf(multiplicativeCodeSet, followBlock);
    factor(multiplicativeFollow);

    while (isSymbolBelongTo(multiplicativeCodeSet)) {
      scanNextToken();
      factor(multiplicativeFollow);
    }
  }
}

void SyntaxAnalyzer::factor(const set<enum TokenCode> &followBlock) {
  auto factorSet = unionOf(leftPar, expressionCodeSet);
  isBelongOrSkipTo(unionOf(factorSet, followBlock), 22);
  if (isSymbolBelongTo(factorSet)) {
    switch (currentToken->getCode()) {
      case leftPar:
        accept(leftPar);
        expression(unionOf(rightPar, followBlock));
        accept(rightPar);
        break;
      case notSy:
        accept(notSy);
        factor(followBlock);
        break;
      case intConst:
        accept(intConst);
        break;
      case realConst:
        accept(realConst);
        break;
      case stringConst:
        accept(stringConst);
        break;
      case nilSy:
        accept(nilSy);
        break;
      case ident:
        accept(ident);
        break;
      default:
        break;
    }
  }
}

void SyntaxAnalyzer::start() {
  program();
}
