#ifndef COMPILER_SRC_MODULE_IO_IOMODULE_H_
#define COMPILER_SRC_MODULE_IO_IOMODULE_H_
#include <fstream>
#include <iostream>
#include "vector"
#include "../../models/io/headers/Error.h"
using namespace std;

/**
 * Модуль ввода-вывода
 */
class IOModule {
 private:
  //Список ошибок
  vector<Error> errors;
  //Поток чтения
  ifstream in;
  //Текущая строка
  string currentLine;
  //Индекс строки
  int lineIdx;
  //Индекс позиции в строке
  int posIdx;
  /** Читет следующую строку из потока */
  void readNextLine();
  /** Закрывает поток на чтение */
  void closeScan();
 public:
  explicit IOModule(const string &_filePath);
  ~IOModule();
  /** Читает следуюий символ из строки */
  char readNextSymbol();
  /** Заносит ошибку в список */
  void logError(int _code);
  /** Вовзаращет список ошибок */
  vector<Error> getErrors();
};

#endif //COMPILER_SRC_MODULE_IO_IOMODULE_H_
