#include <iostream>
#include <sstream>
#include "../headers/Error.h"
#include "../../codes/ErrorCodes.h"

basic_string<char, char_traits<char>, allocator<char>> Error::showError() {
  return "*** " + message + ", строка - " + to_string(textPosition->getLineNumber())
      + ", позиция - " + to_string(textPosition->getPosNumber());
}

Error::Error(int _errorCode, int _line, int _pos) {
  this->message = errorTable.at(_errorCode);
  this->textPosition = make_shared<TextPosition>(_line, _pos);
}

shared_ptr<TextPosition> Error::getTextPosition() {
  return move(textPosition);
}