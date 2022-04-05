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
      /* Должно быть служебное слово PROGRAM */
      case programSy:lexer->getIOModule()->logError(3, offset);
        break;
        /* Должен идти символ  ';' */
      case semicolon:lexer->getIOModule()->logError(14, offset);
        break;
        /* Должен идти символ  '=' */
      case TokenCode::equal:
        lexer->getIOModule()->logError(16, offset);
        break;
        /* Ошибка в типе */
      case arrow:lexer->getIOModule()->logError(10, offset);
        break;
      default:break;
    }
  }
}

void SyntaxAnalyzer::scanNextToken() {
  currentToken = lexer->scanNextToken();
}

void SyntaxAnalyzer::skipTo(TokenCode tokenCode) {
  while (currentToken->getCode() != tokenCode)
    scanNextToken();
  //todo \0?
}

bool SyntaxAnalyzer::isSymbolBelongTo(const set<TokenCode> &block) {
  return block.count(currentToken->getCode()) == 1;
}

void SyntaxAnalyzer::isBelongOrSkipTo(const set<enum TokenCode> &currentBlock, TokenCode block) {
  if (!isSymbolBelongTo(currentBlock)) {
    if (block == beginSy) {
      /* Ожидался BEGIN или раздел описаний */
      lexer->getIOModule()->logError(17);
    } else {
      /* Ошибка в разделе описаний */
      lexer->getIOModule()->logError(18);
    }
    skipTo(block);
  }
}

void SyntaxAnalyzer::program() {
  scanNextToken();
  accept(programSy);
  accept(ident);
  accept(semicolon);
  descriptionSection();
  accept(point);
}

void SyntaxAnalyzer::descriptionSection() {
  /* Ищем блок из раздела описния или пропускаем до BEGIN */
  isBelongOrSkipTo(descriptionBlockSet, beginSy);

  /* Константы */
  if (currentToken->getCode() == constSy)
    constBlock();

  /* Типы */
  if (currentToken->getCode() == typeSy)
    typeBlock();

  /* Переменные */
  if (currentToken->getCode() == varSy)
    varBlock();
}

void SyntaxAnalyzer::constBlock() {
  if (currentToken->getCode() == constSy) {
    accept(constSy);
    do {
      constDescription();
      accept(semicolon);
    } while (currentToken->getCode() == ident);
  }
}

void SyntaxAnalyzer::constDescription() {
  if (currentToken->getCode() == ident) {
    accept(ident);
    accept(TokenCode::equal);
    constRecognition();
  }
}

void SyntaxAnalyzer::constRecognition() {
  if (isSymbolBelongTo(baseTypeCodeSet)) {
    switch (currentToken->getCode()) {
      case intConst:accept(intConst);
        break;
      case realConst:accept(realConst);
        break;
      case stringConst:accept(stringConst);
        break;
      case booleanConst:accept(booleanConst);
        break;
      default:break;
    }
  }
}

void SyntaxAnalyzer::typeBlock() {
  if (currentToken->getCode() == typeSy) {
    accept(typeSy);
    do {
      typeDescription();
      accept(semicolon);
    } while (currentToken->getCode() == ident);
  }
}

void SyntaxAnalyzer::typeDescription() {
  if (currentToken->getCode() == ident) {
    accept(ident);
    accept(TokenCode::equal);
    typeRecognition();
  }
}

void SyntaxAnalyzer::typeRecognition() {
  accept(arrow);
  referenceType();
}

void SyntaxAnalyzer::referenceType() {
  if (baseTypeSet.count(currentToken->toString()) != 1) {/* Неизвестный тип */
    lexer->getIOModule()->logError(400, currentToken->toString().size());
  }
  accept(ident);
}

void SyntaxAnalyzer::varBlock() {
  if (currentToken->getCode() == varSy) {
    accept(varSy);
    do {
      typeDescription();
      auto kek = currentToken->toString();
      accept(semicolon);
    } while (currentToken->getCode() == ident);
  }
}

void SyntaxAnalyzer::varDescription() {

}

void SyntaxAnalyzer::varRecognition() {

}

void SyntaxAnalyzer::factor() {

}

void SyntaxAnalyzer::term() {

}

void SyntaxAnalyzer::start() {
  program();
}

