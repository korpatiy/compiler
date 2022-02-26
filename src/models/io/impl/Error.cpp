#include <iostream>
#include "../headers/Error.h"
#include "../../Codes.h"

void Error::showError() {
  cout << "Возникла ошибка: " << message
       << ", строка - " << textPosition->getLineNumber()
       << ", позиция - " << textPosition->getPosNumber();
}

Error::Error(int _errorCode, int _line, int _pos) {
  this->message = errorTable.at(_errorCode);
  this->textPosition = make_unique<TextPosition>(_line, _pos);
}

unique_ptr<TextPosition, default_delete<TextPosition>> Error::getTextPosition() {
  return move(textPosition);
}
