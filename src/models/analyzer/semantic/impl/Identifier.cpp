#include "../headers/Identifier.h"


Identifier::Identifier(const string &_name, EIdentClass ident_class, shared_ptr<Type> _type) {
  identName = _name;
  identClass = ident_class;
  type = std::move(_type);
}

basic_string<char> Identifier::getName() {
  return identName;
}

shared_ptr<Type> Identifier::getType() {
  return type;
}

EIdentClass Identifier::getIdentClass() {
  return identClass;
}

void Identifier::setType(shared_ptr<Type> _type) {
  type = std::move(_type);
}
