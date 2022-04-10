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
  void skipTo(const set<TokenCode> &block);
  /** Проверяет, пренадлежит ли текущее ключ. слово блоку [block] */
  bool isSymbolBelongTo(const set<TokenCode> &block);
  /**  Проверяет прнадлежность блоку [currentBlock] или пропускает до след. ключевого слова с кодом [block] */
  void isBelongOrSkipTo(const set<enum TokenCode> &currentBlock, int errorCode);
  set<TokenCode> unionOf(const set<TokenCode> &first, const set<TokenCode> &second);
  set<TokenCode> unionOf(TokenCode code, const set<TokenCode> &second);

  /* Грамматики */
  /** Обрабтаывает структуру программы */
  void program();
  /** Обрабаытвает раздел описаний */
  void descriptionSection();
  /** Обрабатывает раздел операторов */
  void operatorSection();

  /* !Индивид. часть - Раздел описания констант */
  void constBlock();
  void constDescription();
  void constRecognition(const set<enum TokenCode> &followBlock);

  /* Раздел описания типов */
  void typeBlock();
  void typeDescription();

  /* Раздел описания переменных */
  void varBlock();
  void varDescription();

  /* Распознование типов */
  void typeRecognition();
  void referenceType();
  void simpleType();

  /* Распознование операторов */
  void operatorRecognition(const set<enum TokenCode> &followBlock);
  void compoundOperator(const set<enum TokenCode> &followBlock);
  void assigmentOperator(const set<enum TokenCode> &followBlock);
  void ifOperator(const set<enum TokenCode> &followBlock);
  void whileOperator(const set<enum TokenCode> &followBlock);
  /* !Индивид. часть - оператор выбора case */
  void caseOperator(const set<enum TokenCode> &followBlock);

  /* Разбор перменных и выражений */
  void variable(const set<enum TokenCode> &followBlock);
  void expression(const set<enum TokenCode> &followBlock);
  void simpleExpression(const set<enum TokenCode> &followBlock);

  void term(const set<enum TokenCode> &followBlock);
  void factor(const set<enum TokenCode> &followBlock);
  void caseVariants(const set<enum TokenCode> &followBlock);
};

#endif //COMPILER_SRC_MODULE_ANALYZER_SYNAXER_SYNTAXANALYZER_H_
