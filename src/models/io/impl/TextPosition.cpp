#include "../headers/TextPosition.h"

TextPosition::TextPosition(int _line, int _position) {
  this->lineNumber = _line;
  this->positionNumber = _position;
}

int TextPosition::getLineNumber() const {
  return lineNumber;
}

int TextPosition::getPosNumber() const {
  return positionNumber;
}

