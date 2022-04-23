#include "../headers/Variant.h"

Variant::Variant(VariantType _variantType) : variantType(_variantType) {
  this->variantType = _variantType;
}

VariantType Variant::getType() {
  return variantType;
}

IntVariant::IntVariant(int _value) : Variant(VT_INTEGER), value(_value) {
  this->value = _value;
}

string IntVariant::toString() {
  return to_string(value);
}

RealVariant::RealVariant(float _value) : Variant(VT_REAL), value(_value) {
  this->value = _value;
}

string RealVariant::toString() {
  return to_string(value);
}

StringVariant::StringVariant(const string &_value) : Variant(VT_STRING), value(_value) {
  this->value = _value;
}

string StringVariant::toString() {
  return this->value;
}

BooleanVariant::BooleanVariant(bool _value) : Variant(VT_BOOLEAN), value(_value) {
  this->value = _value;
}

string BooleanVariant::toString() {
  return to_string(value);
}
