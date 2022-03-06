#ifndef COMPILER_SRC_MODELS_ERROR_H_
#define COMPILER_SRC_MODELS_ERROR_H_

#include "string"
#include "memory"
#include "TextPosition.h"
using namespace std;

/**
 * Класс ошибки
 */
class Error {
 private:
  //Сообщние ошибки
  string message;
  //Позиция ошибки
  shared_ptr<TextPosition> textPosition;
 public:
  Error(int _errorCode, int _line, int _pos);
  ~Error() = default;
  /** Показывает сообщение ошибки */
  basic_string<char, char_traits<char>, allocator<char>> showError();
  /** Возвращает позицию ошибки */
  shared_ptr<TextPosition> getTextPosition();
};

#endif //COMPILER_SRC_MODELS_ERROR_H_
