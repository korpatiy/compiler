#include "IOModule.h"

void IOModule::readNextLine() {
  if (in.is_open()) {
    lineIdx++;
    getline(in, currentLine);
    if (in.eof())
      closeScan();
  }
}

char IOModule::readNextSymbol() {
  if (posIdx < currentLine.size()) {
    return currentLine[posIdx++];
  } else {
    readNextLine();
    posIdx = 0;
    return '\n';
  }
}

void IOModule::closeScan() {
  in.close();
}

vector<Error> IOModule::getErrors() {
  return errors;
}

void IOModule::logError(int _code) {
  this->errors.emplace_back(_code, lineIdx, posIdx);
}

IOModule::IOModule(const string &_filePath) {
  lineIdx = 0;
  posIdx = 0;
  currentLine = "";
  in.open(_filePath, ios::in);
  readNextLine();
}

IOModule::~IOModule() {
  closeScan();
  errors.clear();
}
