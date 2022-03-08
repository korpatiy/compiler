#include <iostream>
#include <sstream>
#include "../headers/Error.h"
#include "../../Codes.h"

basic_string<char, char_traits<char>, allocator<char>> Error::showError() {
  stringstream ss;
  ss << "Возникла ошибка: " << message
     << ", строка - " << textPosition->getLineNumber()
     << ", позиция - " << textPosition->getPosNumber();
  return ss.str();
  //todo
}

Error::Error(int _errorCode, int _line, int _pos) {
  this->message = errorTable.at(_errorCode);
  this->textPosition = make_shared<TextPosition>(_line, _pos);
}

shared_ptr<TextPosition> Error::getTextPosition() {
  return move(textPosition);
}