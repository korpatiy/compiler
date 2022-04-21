#include "../headers/Type.h"

#include <utility>

Type::Type(EType e_type) : type(UNKNOWN_TYPE) {
  type = e_type;
}

EType Type::getTypeName() {
  return type;
}

ScalarType::ScalarType(EType e_type) : Type(e_type) {}

IntType::IntType() : ScalarType(INT_TYPE) {}

RealType::RealType() : ScalarType(REAL_TYPE) {}

StringType::StringType() : ScalarType(STRING_TYPE) {}

BooleanType::BooleanType() : ScalarType(BOOLEAN_TYPE) {}

ReferenceType::ReferenceType(shared_ptr<ScalarType> _refType) : Type(REFERENCE_TYPE) {
  refType = std::move(_refType);
}

shared_ptr<ScalarType> ReferenceType::getRefType() {
  return refType;
}

