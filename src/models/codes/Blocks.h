#ifndef COMPILER_SRC_MODELS_CODES_BLOCKS_H_
#define COMPILER_SRC_MODELS_CODES_BLOCKS_H_

#include "set"
#include "TokenCode.h"
using namespace std;

// Блоки раздела описаний
const set<TokenCode> descriptionBlockSet = set<TokenCode>{constSy, typeSy, varSy};

// Блок стандартных типов кодов
const set<TokenCode> baseTypeCodeSet = set<TokenCode>{intConst, realConst, stringConst, booleanConst};

// Блок операторов
const set<TokenCode> operatorCodeSet = set<TokenCode>{beginSy, ifSy, whileSy, caseSy, ident, semicolon};

// Завершающие блоки
const set<TokenCode> finishCodeSet = set<TokenCode>{endSy, semicolon, point};

/* Операторы */
const set<TokenCode> expressionWithAdditiveCodeSet =
    set<TokenCode>{TokenCode::plus, TokenCode::minus, ident, notSy, intConst, realConst, stringConst, nilSy};

const set<TokenCode> expressionCodeSet =
    set<TokenCode>{ident, notSy, intConst, realConst, stringConst, nilSy};

const set<TokenCode> additiveCodeSet = set<TokenCode>{TokenCode::plus, TokenCode::minus};

// Мультипликативные операторы
const set<TokenCode> multiplicativeCodeSet = set<TokenCode>{star, slash, divSy, modSy, andSy};

// Операторы сравнения
const set<TokenCode> comparisonOperatorCodeSet =
    set<TokenCode>{TokenCode::equal, laterGreater, later, laterEqual, greaterEqual, TokenCode::greater};

#endif //COMPILER_SRC_MODELS_CODES_BLOCKS_H_
