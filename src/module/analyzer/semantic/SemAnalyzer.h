#ifndef COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_
#define COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_

#include "memory"
#include "string"
#include "../../../models/analyzer/semantic/headers/Scope.h"
#include "../../io/IOModule.h"
#include "../../../models/codes/TokenCode.h"

using namespace std;

/**
 * Модуль семантического анализтора
 */
class SemAnalyzer {
 private:
  /* Модуль ввода-вывода */
  shared_ptr<IOModule> ioModule;
  /* Область видимости */
  shared_ptr<Scope> scope;

 public:
  explicit SemAnalyzer(shared_ptr<IOModule> _ioModule);
  ~SemAnalyzer() = default;

  /** Открывает область видимости */
  void openScope();
  /** Инициализарует базовые типы */
  void initTypes();

  /** Возвращает текующую область видимости */
  shared_ptr<Scope> getLocalScope();
  /** Ищет идентификатор с именем [_identName] в переданной области [_findScope] */
  shared_ptr<Identifier> findIdentifier(const shared_ptr<Scope> &_findScope, const string &_identName);
  /** Ищет тип по имени идентификатора [_identName] в переданной области [_findScope] */
  shared_ptr<Type> findType(const shared_ptr<Scope> &_findScope, const string &_identName);
  /** Ищет дубиликаты идентфиктаора с имененм [_identName] или добавляет новый в текущую область */
  void findDuplicateOrAddIdentifier(const string &_identName, const shared_ptr<Identifier> &_identifier);

  /* Методы анализа */

  /** Анализ оператора присвания */
  void analyzeAssigment(EType _varType, EType _exprType);

  /** Анализ для операции отношения
   * @param _type1 - левый тип
   * @param _type2 - правый тип
   * */
  shared_ptr<Type> analyzeRelations(EType _type1, EType _type2);

  /** Анализ для операции добавления
   * @param _type1 - левый тип
   * @param _type2 - правый тип
   * @param _operation - операция между
   */
  shared_ptr<Type> analyzeAdditive(EType _type1,
                                   EType _type2,
                                   TokenCode _operation,
                                   int _tokenSize);

  /** Анализ для операций мультипликации
   * @param _type1 - левый тип
   * @param _type2 - правый тип
   * @param _operation - операция между
   */
  shared_ptr<Type> analyzeMultiplicative(EType _type1,
                                         EType _type2,
                                         TokenCode _operation,
                                         int _tokenSize);

  /** Анализ для операций численных типов */
  shared_ptr<Type> analyzeNumericTypes(EType _type1, EType _type2);

  /** Проверяет правый терм в выражении или выдает ошибку */
  void checkRightTerm(const shared_ptr<struct Type> &_type);
};

#endif //COMPILER_SRC_MODULE_ANALYZER_SEMANTIC_SEMANALYZER_H_
