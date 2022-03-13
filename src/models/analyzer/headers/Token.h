#ifndef COMPILER_SRC_ANALYZERS_TOKEN_H_
#define COMPILER_SRC_ANALYZERS_TOKEN_H_
#include <memory>
#include "Variant.h"
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
 public:
  Token() = default;
  Token(TokenType token_type);
  virtual ~Token() = default;
  TokenType getType();
};

/**
 * Токен идентификтор
 */
class IdentifierToken : public Token {
 public:
  explicit IdentifierToken();
  virtual ~IdentifierToken() = default;
};

/**
 * Токен ключевых слов
 */
class KeywordToken : public Token {
 public:
  explicit KeywordToken();
  virtual ~KeywordToken() = default;
};

/**
 * Токен констант
 */
class ConstantToken : public Token {
 private:
  unique_ptr<Variant> constant;
 public:
  explicit ConstantToken(int _value);
  explicit ConstantToken(double _value);
  explicit ConstantToken(bool _value);
  explicit ConstantToken(const string &_value);
  virtual ~ConstantToken() = default;
  unique_ptr<Variant, default_delete<Variant>> getConstant();
};

#endif //COMPILER_SRC_ANALYZERS_TOKEN_H_
