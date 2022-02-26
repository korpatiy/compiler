#ifndef COMPILER_SRC_MODELS_CONSTANT_H_
#define COMPILER_SRC_MODELS_CONSTANT_H_

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
class Constant {
 private:
  ConstType constType;
 public:
  explicit Constant(ConstType _constType);
  virtual ~Constant() = default;
  ConstType getType();
  virtual string toString() = 0;
};

/**
 * Интовая константа
 */
class IntConstant : public Constant {
 private:
  int value;
 public:
  explicit IntConstant(int _value);
  virtual ~IntConstant() = default;
  string toString() override;
};

/**
 * Вещественная константа
 */
class RealConstant : public Constant {
 private:
  double value;
 public:
  explicit RealConstant(double _value);
  virtual ~RealConstant() = default;
  string toString() override;
};

/**
 * Стринговая константа
 */
class StringConstant : public Constant {
 private:
  string value;
 public:
  explicit StringConstant(const string &_value);
  virtual ~StringConstant() = default;
  string toString() override;
};

/**
 * Булевая константа
 */
class BooleanConstant : public Constant {
 private:
  bool value;
 public:
  explicit BooleanConstant(bool _value);
  virtual ~BooleanConstant() = default;
  string toString() override;
};

#endif //COMPILER_SRC_MODELS_CONSTANT_H_