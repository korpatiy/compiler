#ifndef COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_TYPE_H_
#define COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_TYPE_H_

#include "string"
#include "vector"
#include "memory"

using namespace std;

/**
 * Типы
 */
enum EType {
  UNKNOWN_TYPE,
  INT_TYPE,
  REAL_TYPE,
  STRING_TYPE,
  BOOLEAN_TYPE,
  REFERENCE_TYPE
};

/**
 * Абстрактный тип
 */
class Type {
 private:
  EType type = UNKNOWN_TYPE;
 public:
  explicit Type(EType e_type);
  ~Type() = default;
  /** Возвращает тип */
  EType getTypeName();
};

/**
 * Скалярный стандартный тип
 */
class ScalarType : public Type {
 public:
  explicit ScalarType(EType e_type);
  ~ScalarType() = default;
};

class IntType : public ScalarType {
 public:
  IntType();
  ~IntType() = default;
};

class RealType : public ScalarType {
 public:
  RealType();
  ~RealType() = default;
};

class StringType : public ScalarType {
 public:
  StringType();
  ~StringType() = default;
};

class BooleanType : public ScalarType {
 public:
  BooleanType();
  ~BooleanType() = default;
};

/**
 * Ссылочный тип
 */
class ReferenceType : public Type {
 private:
  /* Ссылка на базовый тип */
  shared_ptr<ScalarType> refType;
 public:
  ReferenceType(shared_ptr<ScalarType> _refType);
  ~ReferenceType() = default;
  /** Возвращает ссылку на базовый тип */
  shared_ptr<ScalarType> getRefType();
};

#endif //COMPILER_SRC_MODELS_ANALYZER_SEMANTIC_TYPE_H_
