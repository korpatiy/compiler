#ifndef COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#define COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
#include "../../io/IOModule.h"
#include "../../../models/analyzer/headers/Token.h"
#include <string>
#include <memory>
using namespace std;

/**
 * Модуль лексического анализатора
 */
class LexAnalyzer {
 private:
  shared_ptr<IOModule> ioModule;

  /* Максимальное целочисленное значение */
  const int MAX_INT_SIZE = INT_MAX;
  /* Максимальная длина строки */
  const int MAX_STRING_SIZE = 255;
  /* Текущий обрабатываемый символ */
  char currentChar{};

  /* Санирование строк */
  shared_ptr<Token> scanString();
  /* Санирование чисел */
  shared_ptr<Token> scanNumber();
  /* Санирование блоков/идентификаторов */
  shared_ptr<Token> scanBlockName();

  /* Санирование символов */
  shared_ptr<Token> scanLater();
  shared_ptr<Token> scanGreater();
  shared_ptr<Token> scanColon();
  shared_ptr<Token> scanPoint();
  shared_ptr<Token> scanStar();
  shared_ptr<Token> scanLeftPar();
  shared_ptr<Token> scanFlPar();
  shared_ptr<Token> scanFrPar();

 public:
  explicit LexAnalyzer(const string &_filePath);
  ~LexAnalyzer() = default;
  /** Сканирует следующий токен */
  shared_ptr<Token> scanNextToken();
  shared_ptr<IOModule> getIOModule();
};

#endif //COMPILER_SRC_ANALYZERS_LEXANALYZER_H_
