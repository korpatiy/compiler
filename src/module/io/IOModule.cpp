#include "IOModule.h"
#include "../../models/analyzer/Analyzer.h"

void IOModule::readNextLine() {

}

vector<Error> IOModule::getErrors() {
  return errors;
}

void IOModule::logError(int _code, int _line, int _pos) {
  this->errors.emplace_back(_code, _line, _pos);
}

void IOModule::scan(const string &_filePath) {

  //todo обратный порядок
  string line;
  ifstream in(_filePath);

  /*auto *analyzer = new Analyzer();
  LexAnalyzer lexAnalyzer = analyzer->lexAnalyzer;*/

  if (in.is_open()) {
    while (getline(in, line)) {
      for (char symbol : line) {
        string str(symbol, 1);
      }
    }
  }

  /*logError(1, 2, 3);
  logError(1, 5, 83);
  logError(1, 6, 33);*/
  in.close();
}
