#include "../headers/Type.h"

Type::Type(EType e_type) : type(UNKNOWN_TYPE) {
  type = e_type;
}

EType Type::getType() {
  return type;
}

ScalarType::ScalarType(EType e_type) : Type(e_type) {}

IntType::IntType() : ScalarType(INT_TYPE) {}

RealType::RealType() : ScalarType(REAL_TYPE) {}

StringType::StringType() : ScalarType(STRING_TYPE) {}

BooleanType::BooleanType() : ScalarType(BOOLEAN_TYPE) {}

ReferenceType::ReferenceType() : Type(REFERENCE_TYPE) {}

EType ReferenceType::getRefType() {
  return refType->getType();
}

