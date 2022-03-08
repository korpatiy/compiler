#include "../headers/TextPosition.h"

TextPosition::TextPosition(int _line, int _position) {
  this->lineNumber = _line;
  this->positionNumber = _position;
}

int TextPosition::getLineNumber() const {
  return this->lineNumber;
}

int TextPosition::getPosNumber() const {
  return this->positionNumber;
}

