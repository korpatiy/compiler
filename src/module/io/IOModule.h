#ifndef COMPILER_SRC_MODULE_IO_IOMODULE_H_
#define COMPILER_SRC_MODULE_IO_IOMODULE_H_
#include <fstream>
#include <iostream>
#include "vector"
#include "../../models/io/headers/Error.h"
#include "../analyzer/LexAnalyzer.h"
using namespace std;

/**
 * Модуль ввода-вывода
 */
class IOModule {
 private:
  //Список ошибок
  vector<Error> errors;
  /** Читет следующую строку из потока */
  void readNextLine();
  /** Заносит ошибку в список */
  void logError(int _code, int _line, int _pos);
 public:
  ~IOModule() = default;
  /** Читает файл */
  void scan(const string& _filePath);
  /** Вовзаращет список ошибок */
  vector<Error> getErrors();
};

#endif //COMPILER_SRC_MODULE_IO_IOMODULE_H_
