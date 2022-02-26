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
  string message;
  unique_ptr<TextPosition> textPosition;
 public:
  Error(int _errorCode, int _line, int _pos);
  ~Error() = default;
  /** Показывает сообщение ошибки */
  void showError();
  unique_ptr<TextPosition, default_delete<TextPosition>> getTextPosition();
};

#endif //COMPILER_SRC_MODELS_ERROR_H_
