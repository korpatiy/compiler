#include <memory>
#include "../headers/Token.h"

Token::Token(TokenType _type) {
  this->tokenType = _type;
}

TokenType Token::getType() {
  return tokenType;
}

IdentifierToken::IdentifierToken() : Token(TT_IDENTIFIER) {}

KeywordToken::KeywordToken() : Token(TT_KEYWORD) {}

ConstantToken::ConstantToken(int _value) : Token(TT_CONSTANT) {
  this->constant = make_unique<IntConstant>(_value);
}

ConstantToken::ConstantToken(double _value) : Token(TT_CONSTANT) {
  this->constant = make_unique<RealConstant>(_value);
}

ConstantToken::ConstantToken(const string& _value) : Token(TT_CONSTANT) {
  this->constant = make_unique<StringConstant>(_value);
}

ConstantToken::ConstantToken(bool _value) : Token(TT_CONSTANT) {
  this->constant = make_unique<BooleanConstant>(_value);
}

unique_ptr<Constant, default_delete<Constant>> ConstantToken::getConstant() {
  return move(constant);
}
