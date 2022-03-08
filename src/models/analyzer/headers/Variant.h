#ifndef COMPILER_SRC_MODELS_VARIANT_H_
#define COMPILER_SRC_MODELS_VARIANT_H_

#include "string"
using namespace std;

/**
 * Типы констант
 */
enum ConstType {
  CT_INTEGER,
  CT_REAL,
  CT_STRING,
  CT_BOOLEAN
};

/**
 * Абстрактная константа
 */
 //todo variant
class Variant {
 private:
  ConstType constType;
 public:
  explicit Variant(ConstType _constType);
  virtual ~Variant() = default;
  ConstType getType();
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
  double value;
 public:
  explicit RealVariant(double _value);
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