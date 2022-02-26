#include <iostream>
#include "models/Constant.h"
#include "models/Token.h"
#include <memory>

int main() {
    auto token = make_unique<ConstantToken>(23);
    auto constant = token->getConstant();
    auto value =constant->toString();
    return 0;
}
