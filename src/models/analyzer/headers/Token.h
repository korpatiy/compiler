#ifndef COMPILER_SRC_ANALYZERS_TOKEN_H_
#define COMPILER_SRC_ANALYZERS_TOKEN_H_
#include <memory>
#include "Variant.h"
#include "../../codes/TokenCode.h"
using namespace std;

/**
 * Абстрактный токен
 */
class Token {
 public:
  /** Типы токенов */
  enum TokenType {
    TT_IDENTIFIER,
    TT_KEYWORD,
    TT_CONSTANT
  };
 private:
  TokenType tokenType;
  TokenCode tokenCode;
 public:
  Token() = default;
  Token(TokenType _tokenType, TokenCode _tokenCode);
  virtual ~Token() = default;
  /** Возвращет строковое значение токена */
  virtual string toString();
  /** Возвращает тип токена */
  TokenType getType();
  /** Возвращает код токена */
  TokenCode getCode();
};

/**
 * Токен идентификтор
 */
class IdentifierToken : public Token {
 private:
  string identName;
 public:
  explicit IdentifierToken(string _identName);
  virtual ~IdentifierToken() = default;
  string toString() override;
};

/**
 * Токен ключевых слов
 */
class KeywordToken : public Token {
 public:
  explicit KeywordToken(TokenCode _tokenCode);
  virtual ~KeywordToken() = default;
};

/**
 * Токен констант
 */
class ConstantToken : public Token {
 private:
  shared_ptr<Variant> constant;
 public:
  /** Целочисленная константа */
  explicit ConstantToken(int _value);
  /** Вещественная константа */
  explicit ConstantToken(float _value);
  /** Булева константа */
  explicit ConstantToken(bool _value);
  /** Строковая константа */
  explicit ConstantToken(const string &_value);
  virtual ~ConstantToken() = default;
  /** Возвращает константу */
  shared_ptr<Variant> getConstant();
  /** Возвращет строковое значение константы */
  string toString() override;
};

#endif //COMPILER_SRC_ANALYZERS_TOKEN_H_
