cmake_minimum_required(VERSION 3.17)
project(compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(compiler src/main.cpp src/module/analyzer/lexer/LexAnalyzer.cpp src/module/analyzer/lexer/LexAnalyzer.h src/models/analyzer/token/impl/Token.cpp src/models/analyzer/token/headers/Token.h src/models/analyzer/token/impl/Variant.cpp src/models/analyzer/token/headers/Variant.h src/module/io/IOModule.cpp src/module/io/IOModule.h src/models/codes/ErrorCodes.h src/models/io/impl/Error.cpp src/models/io/headers/Error.h src/models/io/impl/TextPosition.cpp src/models/io/headers/TextPosition.h src/models/codes/TokenCode.h src/module/analyzer/syntaxer/SyntaxAnalyzer.cpp src/module/analyzer/syntaxer/SyntaxAnalyzer.h src/models/codes/Blocks.h src/module/analyzer/semantic/SemAnalyzer.cpp src/module/analyzer/semantic/SemAnalyzer.h src/models/analyzer/semantic/Type.h src/models/analyzer/semantic/Scope.cpp src/models/analyzer/semantic/Scope.h src/models/analyzer/semantic/Identifier.cpp src/models/analyzer/semantic/Identifier.h)
