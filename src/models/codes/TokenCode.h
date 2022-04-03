#ifndef COMPILER_SRC_MODELS_CODES_TOKENCODE_H_
#define COMPILER_SRC_MODELS_CODES_TOKENCODE_H_

#include "map"

/** Коды токенов */
enum TokenCode {
  /** Группа 2 */
  ifSy = 20,
  doSy = 21,
  ofSy = 22,
  orSy = 23,
  inSy = 24,
  toSy = 25,

  /** Группа 3 */
  endSy = 30,
  varSy = 31,
  divSy = 32,
  andSy = 34,
  notSy = 35,
  forSy = 36,
  modSy = 37,
  nilSy = 38,
  setSy = 39,

  /** Группа 4 */
  thenSy = 40,
  elseSy = 41,
  caseSy = 42,
  fileSy = 43,
  gotoSy = 44,
  typeSy = 45,
  withSy = 46,

  /** Группа 5 */
  beginSy = 50,
  whileSy = 51,
  arraySy = 52,
  constSy = 53,
  labelSy = 54,
  untilSy = 55,

  /** Группа 6 */
  downtoSy = 61,
  packedSy = 62,
  recordSy = 63,
  repeatSy = 64,

  /** Группа 7 */
  programSy = 70,

  /** Группа 8 */
  functionSy = 80,

  /** Группа 9 */
  procedureSy = 90,

  /** '*' */
  star = 100,
  /** '/' */
  slash = 101,
  /** '=' */
  equal = 102,
  /** ',' */
  comma = 103,
  /** ';' */
  semicolon = 104,
  /** ':' */
  colon = 105,
  /** '.' */
  point = 106,
  /** '^' */
  arrow = 107,
  /** '(' */
  leftPar = 108,
  /** ')' */
  rightPar = 109,
  /** '[' */
  lBracket = 110,
  /** ']' */
  rBracket = 111,
  /** '{' */
  flPar = 112,
  /** '}' */
  frPar = 113,
  /** '<' */
  later = 114,
  /** '>' */
  greater = 115,
  /** '<=' */
  laterEqual = 116,
  /** '=>' */
  greaterEqual = 117,
  /** '<>' */
  laterGreater = 118,
  /** '+' */
  plus = 119,
  /** '-' */
  minus = 120,
  /** '(*' */
  lComment = 121,
  /** '*)' */
  rComment = 122,
  /** ':=' */
  assign = 123,
  /** '..' */
  twoPoints = 124,

  /** Идентификатор */
  ident = 200,

  /** Целочисленая константа */
  intConst = 300,
  /** Вещесвтенная константа */
  realConst = 301,
  /** Строковая константа */
  stringConst = 302,
  /** Булевая константа */
  booleanConst = 303,
};

/** Таблица сключевых слов: <название> - <код токена> */
const map<string, TokenCode> keywordMap = {
    {"do", doSy},
    {"if", ifSy},
    {"in", inSy},
    {"of", ofSy},
    {"or", orSy},
    {"to", toSy},
    {"and", andSy},
    {"div", divSy},
    {"end", endSy},
    {"for", forSy},
    {"for", forSy},
    {"mod", modSy},
    {"nil", nilSy},
    {"not", notSy},
    {"set", setSy},
    {"var", varSy},
    {"case", caseSy},
    {"else", elseSy},
    {"file", fileSy},
    {"goto", gotoSy},
    {"then", thenSy},
    {"type", typeSy},
    {"with", withSy},
    {"array", arraySy},
    {"begin", beginSy},
    {"const", constSy},
    {"label", labelSy},
    {"until", untilSy},
    {"while", whileSy},
    {"downto", downtoSy},
    {"packed", packedSy},
    {"record", recordSy},
    {"repeat", repeatSy},
    {"program", programSy},
    {"function", functionSy},
    {"procedure", procedureSy},
};

#endif //COMPILER_SRC_MODELS_CODES_TOKENCODE_H_
