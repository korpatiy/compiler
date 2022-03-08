#include "../headers/Variant.h"

Variant::Variant(ConstType _constType) : constType(_constType) {
  this->constType = _constType;
}

ConstType Variant::getType() {
  return constType;
}

IntVariant::IntVariant(int _value) : Variant(CT_INTEGER), value(_value) {
  this->value = _value;
}

string IntVariant::toString() {
  return to_string(value);
}

RealVariant::RealVariant(double _value) : Variant(CT_REAL), value(_value) {
  this->value = _value;
}

string RealVariant::toString() {
  return to_string(value);
}

StringVariant::StringVariant(const string &_value) : Variant(CT_STRING), value(_value) {
  this->value = _value;
}

string StringVariant::toString() {
  return this->value;
}

BooleanVariant::BooleanVariant(bool _value) : Variant(CT_BOOLEAN), value(_value) {
  this->value = _value;
}

string BooleanVariant::toString() {
  return to_string(value);
}
