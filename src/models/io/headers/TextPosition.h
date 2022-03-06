#ifndef COMPILER_SRC_MODELS_IO_HEADERS_TEXTPOSITION_H_
#define COMPILER_SRC_MODELS_IO_HEADERS_TEXTPOSITION_H_

/**
 * Класс для формирования положения ошибки
 */
class TextPosition {
 private:
  //Номер строки
  int lineNumber;
  //Номер позиции в строке
  int positionNumber;
 public:
  TextPosition(int _line, int _position);
  virtual ~TextPosition() = default;
  int getLineNumber() const;
  int getPosNumber() const;
};

#endif //COMPILER_SRC_MODELS_IO_HEADERS_TEXTPOSITION_H_
