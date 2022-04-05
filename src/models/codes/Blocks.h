#ifndef COMPILER_SRC_MODELS_CODES_BLOCKS_H_
#define COMPILER_SRC_MODELS_CODES_BLOCKS_H_

#include "set"
#include "TokenCode.h"
using namespace std;

// Блоки раздела описаний
const set<TokenCode> descriptionBlockSet = set<TokenCode>{constSy, typeSy, varSy};

// Блок стандартных типов кодов
const set<TokenCode> baseTypeCodeSet = set<TokenCode>{intConst, realConst, stringConst, booleanConst};

// Блок стандартных типов
const set<string> baseTypeSet = set<string>{"integer", "real", "string", "boolean"};

#endif //COMPILER_SRC_MODELS_CODES_BLOCKS_H_
