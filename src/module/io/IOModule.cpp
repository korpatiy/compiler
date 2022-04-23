#include "IOModule.h"

void IOModule::readNextLine() {
  if (in.is_open()) {
    lineIdx++;
    getline(in, currentLine);
    out << currentLine + "\n";
    if (in.eof())
      in.close();
  } else {
    reachedEndOfFile = true;
  }
}

char IOModule::scanNextSymbol() {
  if (posIdx < currentLine.size()) {
    return currentLine[posIdx++];
  } else {
    readNextLine();
    if (!reachedEndOfFile) {
      posIdx = 0;
      return '\n';
    } else {
      return '\0';
    }
  }
}

char IOModule::peekSymbol(int _offset) {
  return posIdx + _offset < currentLine.size() ?
         currentLine[posIdx + _offset] :
         '\n';
}

void IOModule::closeScan() {
  in.close();
  out << "\n-----Анализ закончен, кол-во ошибок: " << errors.size() << "------" << "\n";
  out.close();
}

vector<Error> IOModule::getErrors() {
  return errors;
}

void IOModule::logError(int _code, int _offset) {
  int offsetPos = posIdx - _offset;
  this->errors.emplace_back(_code, lineIdx, offsetPos);
  out << string(offsetPos, ' ') << "^" << "\n";
  out << "*** " << "(Код - " << _code << ") " << errors.back().showError() << "\n";
}

IOModule::IOModule(const string &_filePath) {
  lineIdx = 0;
  posIdx = 0;
  currentLine = "";
  in.open(_filePath, ios::in);
  out.open("C:/Users/Slava/Desktop/compiler/src/listingSem.txt");
  readNextLine();
}

IOModule::~IOModule() {
  closeScan();
  errors.clear();
}
