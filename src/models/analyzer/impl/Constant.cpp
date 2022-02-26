#include "../headers/Constant.h"

Constant::Constant(ConstType _constType) : constType(_constType) {
  this->constType = _constType;
}

ConstType Constant::getType() {
  return constType;
}

IntConstant::IntConstant(int _value) : Constant(CT_INTEGER), value(_value) {
  this->value = _value;
}

string IntConstant::toString() {
  return to_string(value);
}

RealConstant::RealConstant(double _value) : Constant(CT_REAL), value(_value) {
  this->value = _value;
}

string RealConstant::toString() {
  return to_string(value);
}

StringConstant::StringConstant(const string &_value) : Constant(CT_STRING), value(_value) {
  this->value = _value;
}

string StringConstant::toString() {
  return this->value;
}

BooleanConstant::BooleanConstant(bool _value) : Constant(CT_BOOLEAN), value(_value) {
  this->value = _value;
}

string BooleanConstant::toString() {
  return to_string(value);
}
