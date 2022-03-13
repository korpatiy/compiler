#ifndef COMPILER_SRC_MODELS_CODES_SYMBOLCODES_H_
#define COMPILER_SRC_MODELS_CODES_SYMBOLCODES_H_

/** Коды символов */
enum SymbolCodes {
  /** '*' */
  star = 1,
  /** '/' */
  slash = 2,
  /** '=' */
  equal = 3,
  /** ',' */
  comma = 4,
  /** ';' */
  semicolon = 5,
  /** ':' */
  colon = 6,
  /** '.' */
  point = 7,
  /** '^' */
  arrow = 8,
  /** '(' */
  leftPar = 9,
  /** ')' */
  rightPar = 10,
  /** '[' */
  lBracket = 11,
  /** ']' */
  rBracket = 12,
  /** '{' */
  flPar = 13,
  /** '}' */
  frPar = 14,
  /** '<' */
  later = 15,
  /** '>' */
  greater = 16,
  /** '<=' */
  laterEqual = 17,
  /** '=>' */
  greaterEqual = 18,
  /** '<>' */
  laterGreater = 19,
  /** '+' */
  plus = 20,
  /** '-' */
  minus = 21,
  /** '(*' */
  lComment = 22,
  /** '*)' */
  rComment = 23,
  /** ':=' */
  assign = 24,
  /** '..' */
  twoPoints = 25,

  /** Идентификатор */
  ident = 26,

  /** Целочисленая константа */
  intConst = 27,
  /** Вещесвтенная константа */
  realConst = 27,
  /** Строковая константа */
  stringConst = 28,
  /** Булевая константа */
  booleanConst = 28,
};

#endif //COMPILER_SRC_MODELS_CODES_SYMBOLCODES_H_
