#ifndef COMPILER_SRC_MODULE_ANALYZER_SYNAXER_SYNTAXANALYZER_H_
#define COMPILER_SRC_MODULE_ANALYZER_SYNAXER_SYNTAXANALYZER_H_

#include <set>
#include "memory"
#include "string"
#include "../lexer/LexAnalyzer.h"
using namespace std;

/**
 * Модуль синтаксического анализатора
 */
class SyntaxAnalyzer {
 private:
  /* Лексер */
  unique_ptr<LexAnalyzer> lexer;
  /* Текущий токен */
  shared_ptr<Token> currentToken;

 public:
  explicit SyntaxAnalyzer(const string &_filePath);
  ~SyntaxAnalyzer() = default;

  /** Стартует выполнение анализа */
  void start();
 private:
  /** Сканирует следующий токен */
  void scanNextToken();
  /**  */
  void accept(TokenCode tokenCode);
  /** Пропускает до след. ключевогшо слова с кодом [tokenCode] */
  void skipTo(TokenCode tokenCode);
  /** Проверяет, пренадлежит ли текущее ключ. слово блоку [block] */
  bool isSymbolBelongTo(const set<TokenCode> &block);
  /**  Проверяет прнадлежность блоку [currentBlock] или пропускает до след. ключевого слова с кодом [block] */
  void isBelongOrSkipTo(const set<enum TokenCode> &currentBlock, TokenCode block);

  /* Грамматики */
  /** Обрабтаывает структуру программы */
  void program();
  /** Обрабаытвает раздел описаний */
  void descriptionSection();

  /* !Индивид. часть - Раздел описания констант */
  void constBlock();
  void constDescription();
  void constRecognition();

  /* Раздел описания типов */
  void typeBlock();
  void typeDescription();
  void typeRecognition();
  void referenceType();

  /* Раздел описания переменных */
  void varBlock();
  void varDescription();
  void varRecognition();

  /* */
  void term();
  void factor();
};

#endif //COMPILER_SRC_MODULE_ANALYZER_SYNAXER_SYNTAXANALYZER_H_
