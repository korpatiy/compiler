#include <memory>
#include <utility>
#include "../headers/Token.h"

Token::Token(Token::TokenType _tokenType, TokenCode _tokenCode) {
  this->tokenType = _tokenType;
  this->tokenCode = _tokenCode;
}

Token::TokenType Token::getType() {
  return this->tokenType;
}

TokenCode Token::getCode() {
  return this->tokenCode;
}

string Token::toString() {
  return toStringMap.at(tokenCode);
}

IdentifierToken::IdentifierToken(string _identName) : Token(TokenType::TT_IDENTIFIER, TokenCode::ident) {
  this->identName = std::move(_identName);
}

string IdentifierToken::toString() {
  return identName;
}

KeywordToken::KeywordToken(TokenCode _tokenCode) : Token(TokenType::TT_KEYWORD, _tokenCode) {}

ConstantToken::ConstantToken(int _value) : Token(TokenType::TT_CONSTANT, TokenCode::intConst) {
  this->constant = make_shared<IntVariant>(_value);
}

ConstantToken::ConstantToken(float _value) : Token(TokenType::TT_CONSTANT, TokenCode::realConst) {
  this->constant = make_shared<RealVariant>(_value);
}

ConstantToken::ConstantToken(const string &_value) : Token(TokenType::TT_CONSTANT, TokenCode::stringConst) {
  this->constant = make_shared<StringVariant>(_value);
}

ConstantToken::ConstantToken(bool _value) : Token(TokenType::TT_CONSTANT, TokenCode::booleanConst) {
  this->constant = make_shared<BooleanVariant>(_value);
}

shared_ptr<Variant> ConstantToken::getConstant() {
  return constant;
}

string ConstantToken::toString() {
  return getConstant()->toString();
}
