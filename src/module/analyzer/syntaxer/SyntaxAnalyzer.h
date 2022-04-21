#ifndef COMPILER_SRC_MODULE_ANALYZER_SYNAXER_SYNTAXANALYZER_H_
#define COMPILER_SRC_MODULE_ANALYZER_SYNAXER_SYNTAXANALYZER_H_

#include <set>
#include "memory"
#include "string"
#include "../lexer/LexAnalyzer.h"
#include "../../../models/analyzer/token/headers/Token.h"
#include "../semantic/SemAnalyzer.h"
using namespace std;

/**
 * Модуль синтаксического анализатора
 */
class SyntaxAnalyzer {
 private:
  /* Лексер */
  unique_ptr<LexAnalyzer> lexer;
  /* Семансер */
  unique_ptr<SemAnalyzer> semancer;
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
  /** Принимает переданный токен и сверяет с текущем */
  void accept(TokenCode tokenCode);
  /** Пропускает до первого встретившегося токена в [block] */
  void skipTo(const set<TokenCode> &block);
  /** Проверяет, пренадлежит ли текущее ключ. слово блоку [block] */
  bool isSymbolBelongTo(const set<TokenCode> &block);
  /**  Проверяет прнадлежность блоку [block] или пропускает до первого встречного, [errorCode] - код ошибки в разделах */
  void isBelongOrSkipTo(const set<enum TokenCode> &block, int errorCode);
  /** Объединяет блоки [first] и [second] */
  set<TokenCode> unionOf(const set<TokenCode> &first, const set<TokenCode> &second);
  /** Добавляет [code] в переданный блок [block] */
  set<TokenCode> unionOf(TokenCode code, const set<TokenCode> &block);

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
  shared_ptr<Type> constRecognition(const set<enum TokenCode> &followBlock);

  /* Раздел описания типов */
  void typeBlock();
  void typeDescription();

  /* Раздел описания переменных */
  void varBlock();
  void varDescription();

  /* Распознование типов */
  shared_ptr<Type> typeRecognition();
  shared_ptr<Type> referenceType();
  shared_ptr<Type> simpleType();

  /* Распознование операторов */
  void operatorRecognition(const set<enum TokenCode> &followBlock);
  void compoundOperator(const set<enum TokenCode> &followBlock);
  void assigmentOperator(const set<enum TokenCode> &followBlock);
  void ifOperator(const set<enum TokenCode> &followBlock);
  void whileOperator(const set<enum TokenCode> &followBlock);
  /* !Индивид. часть - оператор выбора case */
  void caseOperator(const set<enum TokenCode> &followBlock);
  void caseVariants(const set<enum TokenCode> &followBlock, EType followType);

  /* Разбор перменных и выражений */
  shared_ptr<Type> variable(const set<enum TokenCode> &followBlock);
  shared_ptr<Type> expression(const set<enum TokenCode> &followBlock);
  shared_ptr<Type> simpleExpression(const set<enum TokenCode> &followBlock);

  shared_ptr<Type> term(const set<enum TokenCode> &followBlock);
  shared_ptr<Type> factor(const set<enum TokenCode> &followBlock);
  shared_ptr<Identifier> getIdent();
};

#endif //COMPILER_SRC_MODULE_ANALYZER_SYNAXER_SYNTAXANALYZER_H_
