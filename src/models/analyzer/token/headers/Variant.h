#ifndef COMPILER_SRC_MODELS_VARIANT_H_
#define COMPILER_SRC_MODELS_VARIANT_H_

#include "string"
using namespace std;

/**
 * Варианты констант
 */
enum VariantType {
  VT_INTEGER,
  VT_REAL,
  VT_STRING,
  VT_BOOLEAN
};

class Variant {
 private:
  VariantType variantType;
 public:
  explicit Variant(VariantType _variantType);
  virtual ~Variant() = default;
  VariantType getType();
  virtual string toString() = 0;
};

/**
 * Интовая константа
 */
class IntVariant : public Variant {
 private:
  int value;
 public:
  explicit IntVariant(int _value);
  virtual ~IntVariant() = default;
  string toString() override;
};

/**
 * Вещественная константа
 */
class RealVariant : public Variant {
 private:
  float value;
 public:
  explicit RealVariant(float _value);
  virtual ~RealVariant() = default;
  string toString() override;
};

/**
 * Стринговая константа
 */
class StringVariant : public Variant {
 private:
  string value;
 public:
  explicit StringVariant(const string &_value);
  virtual ~StringVariant() = default;
  string toString() override;
};

/**
 * Булевая константа
 */
class BooleanVariant : public Variant {
 private:
  bool value;
 public:
  explicit BooleanVariant(bool _value);
  virtual ~BooleanVariant() = default;
  string toString() override;
};

#endif //COMPILER_SRC_MODELS_VARIANT_H_