#include <memory>
#include "../headers/Token.h"

Token::Token(TokenType _tokenType) {
  this->tokenType = _tokenType;
}

Token::TokenType Token::getType() {
  return this->tokenType;
}

IdentifierToken::IdentifierToken() : Token(TokenType::TT_IDENTIFIER) {}

KeywordToken::KeywordToken() : Token(TokenType::TT_KEYWORD) {}

ConstantToken::ConstantToken(int _value) : Token(TokenType::TT_CONSTANT) {
  this->constant = make_unique<IntVariant>(_value);
}

ConstantToken::ConstantToken(double _value) : Token(TokenType::TT_CONSTANT) {
  this->constant = make_unique<RealVariant>(_value);
}

ConstantToken::ConstantToken(const string &_value) : Token(TokenType::TT_CONSTANT) {
  this->constant = make_unique<StringVariant>(_value);
}

ConstantToken::ConstantToken(bool _value) : Token(TokenType::TT_CONSTANT) {
  this->constant = make_unique<BooleanVariant>(_value);
}

unique_ptr<Variant, default_delete<Variant>> ConstantToken::getConstant() {
  return move(constant);
}
