#include "LexAnalyzer.h"
#include "../../../models/codes/ErrorCodes.h"

shared_ptr<Token> LexAnalyzer::scanNextToken() {
  currentChar = ioModule->scanNextSymbol();
  while (currentChar == '\n' || currentChar == ' ')
    currentChar = ioModule->scanNextSymbol();

  auto token = shared_ptr<Token>();

  switch (currentChar) {
    case '\'': token = scanString();
      break;
    case '<': token = scanLater();
      break;
    case '>': token = scanGreater();
      break;
    case ':': token = scanColon();
      break;
    case '.': token = scanPoint();
      break;
    case '*': token = scanStar();
      break;
    case '(': token = scanLeftPar();
      break;
    case '{': token = scanFlPar();
      break;
    case '}': token = scanFrPar();
      break;
    case '+': token = make_shared<KeywordToken>(TokenCode::plus);
      break;
    case '-':token = make_shared<KeywordToken>(TokenCode::minus);
      break;
    case '/': token = make_shared<KeywordToken>(TokenCode::slash);
      break;
    case ')': token = make_shared<KeywordToken>(TokenCode::rightPar);
      break;
    case ';': token = make_shared<KeywordToken>(TokenCode::semicolon);
      break;
    case '=': token = make_shared<KeywordToken>(TokenCode::equal);
      break;
    case ',': token = make_shared<KeywordToken>(TokenCode::comma);
      break;
    case '^': token = make_shared<KeywordToken>(TokenCode::arrow);
      break;
    case '[': token = make_shared<KeywordToken>(TokenCode::lBracket);
      break;
    case ']': token = make_shared<KeywordToken>(TokenCode::rBracket);
      break;
    case '\0': token = make_shared<KeywordToken>(TokenCode::endOfFile);
      break;
    default:
      if (isdigit(currentChar))
        token = scanNumber();
      else if (isalpha(currentChar))
        token = scanBlockName();
      else {
        /* Запрещенный символ */
        ioModule->logError(6);
        token = scanNextToken();
      }
  }
  return move(token);
}

LexAnalyzer::LexAnalyzer(const string &_filePath) {
  this->ioModule = make_unique<IOModule>(_filePath);
}

shared_ptr<Token> LexAnalyzer::scanString() {
  char charConst = ioModule->scanNextSymbol();
  if (charConst == '\'' || charConst == '\n') {
    /* Ошибка в символьной константе */
    ioModule->logError(75, 1);
    return make_shared<ConstantToken>(charConst);
  }

  string str;
  while (charConst != '\'') {
    str += charConst;

    if (str.length() > MAX_STRING_SIZE) {
      /* Слишком длинная строковая константа */
      ioModule->logError(76);
      return make_shared<ConstantToken>(str);
    }

    charConst = ioModule->scanNextSymbol();
    if (charConst == '\n') {
      /* Ошибка в символьной константе */
      ioModule->logError(75);
      return make_shared<ConstantToken>(str);
    }
  }

  return move(make_shared<ConstantToken>(str));
}

shared_ptr<Token> LexAnalyzer::scanNumber() {
  int number = currentChar - '0';
  char nextChar = ioModule->peekSymbol();

  while (isdigit(nextChar)) {
    currentChar = ioModule->scanNextSymbol();
    int digit = currentChar - '0';

    if (number < MAX_INT_SIZE / 10 ||
        number < MAX_INT_SIZE / 10 && digit <= MAX_INT_SIZE % 10)
      number = 10 * number + digit;
    else {
      /* Целая константа превышает предел */
      ioModule->logError(203);
      break;
    }
    nextChar = ioModule->peekSymbol();
  }

  if(number == 228){
    printf("ds");
  }
  /* Целая константа */
  if (nextChar != '.') {
    return move(make_shared<ConstantToken>(number));
  }

  nextChar = ioModule->peekSymbol(1);
  if (!isdigit(nextChar)) {
    if (isalpha(nextChar)) {
      ioModule->logError(201);
    }
    return move(make_shared<ConstantToken>(number));
  }

  /* Пропускаем точку */
  ioModule->scanNextSymbol();
  nextChar = ioModule->peekSymbol();

  int realNumberPart = 0;
  int rad = 1;
  while (isdigit(nextChar)) {
    currentChar = ioModule->scanNextSymbol();
    int digit = currentChar - '0';

    if (realNumberPart < MAX_INT_SIZE / 10 ||
        realNumberPart < MAX_INT_SIZE / 10 && digit <= MAX_INT_SIZE % 10) {
      realNumberPart = 10 * realNumberPart + digit;
      rad *= 10;
    } else {
      /* Cлишком большая вещественная константа */
      ioModule->logError(207);
      break;
    }
    nextChar = ioModule->peekSymbol();
  }

  float realNumber = static_cast<float>(number) +
      static_cast<float>(realNumberPart) / static_cast<float>(rad);
  return move(make_shared<ConstantToken>(realNumber));
}

shared_ptr<Token> LexAnalyzer::scanBlockName() {
  string blockName(1, currentChar);
  auto token = shared_ptr<Token>();

  char nextChar = ioModule->peekSymbol();
  while ((isalpha(nextChar) || isdigit(nextChar)) || nextChar == '_') {
    blockName += ioModule->scanNextSymbol();
    nextChar = ioModule->peekSymbol();
  }

  if (keywordMap.count(blockName) == 1)
    token = make_shared<KeywordToken>(keywordMap.at(blockName));
  else token = make_shared<IdentifierToken>(blockName);

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanLater() {
  char nextChar = ioModule->peekSymbol();

  auto token = shared_ptr<Token>();

  switch (nextChar) {
    case '=':token = make_shared<KeywordToken>(TokenCode::laterEqual);
      ioModule->scanNextSymbol();
      break;
    case '>':token = make_shared<KeywordToken>(TokenCode::laterGreater);
      ioModule->scanNextSymbol();
      break;
    default:token = make_shared<KeywordToken>(TokenCode::later);
      break;
  }

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanGreater() {
  char nextChar = ioModule->peekSymbol();

  auto token = shared_ptr<Token>();

  if (nextChar == '=') {
    token = make_shared<KeywordToken>(TokenCode::greaterEqual);
    ioModule->scanNextSymbol();
  } else
    token = make_shared<KeywordToken>(TokenCode::greater);

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanColon() {
  char nextChar = ioModule->peekSymbol();

  auto token = shared_ptr<Token>();

  if (nextChar == '=') {
    token = make_shared<KeywordToken>(TokenCode::assign);
    ioModule->scanNextSymbol();
  } else
    token = make_shared<KeywordToken>(TokenCode::colon);

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanPoint() {
  char nextChar = ioModule->peekSymbol();
  auto token = shared_ptr<Token>();

  if (nextChar == '.') {
    token = make_shared<KeywordToken>(TokenCode::twoPoints);
    ioModule->scanNextSymbol();
  } else
    token = make_shared<KeywordToken>(TokenCode::point);

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanLeftPar() {
  char nextChar = ioModule->peekSymbol();

  auto token = shared_ptr<Token>();

  if (nextChar == '*') {
    char prev = currentChar;
    currentChar = ioModule->scanNextSymbol();

    while ((prev != '*' || currentChar != ')') && currentChar != '\0') {
      prev = currentChar;
      currentChar = ioModule->scanNextSymbol();
    }

    if (prev == '*' && currentChar == ')') {
      token = scanNextToken();
    } else {
      /* Комментарий не закрыт */
      ioModule->logError(86);
      return nullptr;
    }
  } else
    token = make_shared<KeywordToken>(TokenCode::leftPar);

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanStar() {
  char nextChar = ioModule->peekSymbol();

  auto token = shared_ptr<Token>();

  if (nextChar == ')') {
    currentChar = ioModule->scanNextSymbol();
    /* Комментарий не открыт */
    ioModule->logError(85);
    token = make_shared<KeywordToken>(TokenCode::rComment);
  } else
    token = make_shared<KeywordToken>(TokenCode::star);

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanFlPar() {
  auto token = shared_ptr<Token>();

  while (!(currentChar == '}' || currentChar == '\0')) {
    currentChar = ioModule->scanNextSymbol();
  }

  if (currentChar == '}')
    token = scanNextToken();
  else {
    /* Комментарий не закрыт */
    ioModule->logError(86);
    return nullptr;
  }

  return move(token);
}

shared_ptr<Token> LexAnalyzer::scanFrPar() {
  /* Комментарий не открыт */
  ioModule->logError(85);
  return move(make_shared<KeywordToken>(TokenCode::frPar));
}

shared_ptr<IOModule> LexAnalyzer::getIOModule() {
  /* В данном случае не передаем управление, модуль ввода/ввода все еще пренадлежит лексеру, но управляет им еще и синатксер */
  return ioModule;
}