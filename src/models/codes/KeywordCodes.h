#ifndef COMPILER_SRC_MODELS_CODES_KEYWORDCODES_H_
#define COMPILER_SRC_MODELS_CODES_KEYWORDCODES_H_

/** Коды спец. слов */
enum KeywordCodes {
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
  program = 70,

  /** Группа 8 */
  function = 80,

  /** Группа 9 */
  procedure = 90,
};

#endif //COMPILER_SRC_MODELS_CODES_KEYWORDCODES_H_
