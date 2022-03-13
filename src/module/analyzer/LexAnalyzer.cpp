#include "LexAnalyzer.h"
#include "../../models/codes/KeywordCodes.h"

unique_ptr<Token, default_delete<Token>> LexAnalyzer::scanNextToken() {
  char symbol = ioModule->readNextSymbol();
  while (symbol == '\n')
    symbol = ioModule->readNextSymbol();

  unique_ptr<Token> token = make_unique<Token>();

  switch (symbol) {
    case '\'': token = scanString();
      break;
    case '<': return scanLater();
      break;
    case '>': return scanGreater();
      break;
    case ':': return scanColon();
      break;
    case '.': return scanPoint();
      break;
    case '*': return scanStar();
      break;
    case '(': return scanLeftPar();
      break;
    case '{': return scanFlPar();
      break;
    case '}': return scanFrPar();
      break;
    default: return;
      break;
  }

  return move(token);
}

LexAnalyzer::LexAnalyzer(const string &_filePath) {
  ioModule = make_unique<IOModule>(_filePath);
}

unique_ptr<ConstantToken, default_delete<ConstantToken>> LexAnalyzer::scanString() {
  char charConst = ioModule->readNextSymbol();
  if (charConst == '\'' || charConst == '\n') {
    ioModule->logError(75);
    //todo?
    return nullptr;
  }

  string str;
  while (charConst != '\'') {
    str += charConst;

    if (str.length() > MAX_STRING_SIZE) {
      ioModule->logError(76);
      //todo?
      return nullptr;
    }

    charConst = ioModule->readNextSymbol();
    if (charConst == '\n') {
      ioModule->logError(75);
      //todo?
      return nullptr;
    }
  }

  return move(make_unique<ConstantToken>(str));
}

void LexAnalyzer::scanNumber() {

}

void LexAnalyzer::scanLater() {

  //KeywordCodes::caseSy
  //move(make_unique<KeywordToken>())
}

void LexAnalyzer::scanGreater() {

}

void LexAnalyzer::scanColon() {

}

void LexAnalyzer::scanPoint() {

}

void LexAnalyzer::scanStar() {

}

void LexAnalyzer::scanFlPar() {

}

void LexAnalyzer::scanFrPar() {

}
void LexAnalyzer::scanLeftPar() {

}
