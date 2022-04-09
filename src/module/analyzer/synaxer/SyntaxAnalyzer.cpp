#include "SyntaxAnalyzer.h"
#include "../../../models/codes/Blocks.h"

SyntaxAnalyzer::SyntaxAnalyzer(const string &_filePath) {
  lexer = make_unique<LexAnalyzer>(_filePath);
}

void SyntaxAnalyzer::accept(TokenCode tokenCode) {
  if (currentToken->getCode() == tokenCode)
    scanNextToken();
  else {
    int offset = currentToken->toString().size();
    /* Должно быть служебное слово PROGRAM */
    switch (tokenCode) {
      case programSy:
        /* Должно быть служебное слово PROGRAM */
        lexer->getIOModule()->logError(3, offset);
        break;
      case semicolon:
        /* Должен идти символ  ';' */
        lexer->getIOModule()->logError(14, offset);
        break;
      case TokenCode::equal:
        /* Должен идти символ  '=' */
        lexer->getIOModule()->logError(16, offset);
        break;
      case arrow:
        /* Ошибка в типе */
        lexer->getIOModule()->logError(10, offset);
        break;
      case colon:
        /* Должен идти символ  ':' */
        lexer->getIOModule()->logError(5, offset);
        break;
      default:break;
    }
  }
}

void SyntaxAnalyzer::scanNextToken() {
  currentToken = lexer->scanNextToken();
}

void SyntaxAnalyzer::skipTo(TokenCode code) {
  while (currentToken->getCode() != code) {
    scanNextToken();
    if (currentToken->getCode() == endOfFile)
      break;
  }
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

void SyntaxAnalyzer::isBelongOrSkipTo(const set<enum TokenCode> &currentBlock, int errorCode) {
  if (!isSymbolBelongTo(currentBlock)) {
    lexer->getIOModule()->logError(errorCode);
    skipTo(currentBlock);
  }
}

void SyntaxAnalyzer::program() {
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
    accept(ident);
    accept(TokenCode::equal);
    constRecognition();
  }
}

void SyntaxAnalyzer::constRecognition() {
  if (isSymbolBelongTo(baseTypeCodeSet) || currentToken->getCode() == ident) {
    switch (currentToken->getCode()) {
      case intConst:accept(intConst);
        break;
      case realConst:accept(realConst);
        break;
      case stringConst:accept(stringConst);
        break;
      case booleanConst:accept(booleanConst);
      case ident: accept(ident);
        break;
      default:break;
    }
  }
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
  scanTypeAndAccept();
}

void SyntaxAnalyzer::simpleType() {
  scanTypeAndAccept();
}

void SyntaxAnalyzer::scanTypeAndAccept() {
  accept(ident);
}

void SyntaxAnalyzer::operatorSection() {
  if (currentToken->getCode() != beginSy) {
    lexer->getIOModule()->logError(18);
    skipTo(beginSy);
  }
}

void SyntaxAnalyzer::factor() {

}

void SyntaxAnalyzer::term() {

}
void SyntaxAnalyzer::start() {
  program();
}

