cmake_minimum_required(VERSION 3.17)
project(compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(compiler src/main.cpp src/module/analyzer/lexer/LexAnalyzer.cpp src/module/analyzer/lexer/LexAnalyzer.h src/models/analyzer/impl/Token.cpp src/models/analyzer/headers/Token.h src/models/analyzer/impl/Variant.cpp src/models/analyzer/headers/Variant.h src/module/io/IOModule.cpp src/module/io/IOModule.h src/models/codes/ErrorCodes.h src/models/io/impl/Error.cpp src/models/io/headers/Error.h src/models/io/impl/TextPosition.cpp src/models/io/headers/TextPosition.h src/models/codes/TokenCode.h src/module/analyzer/synaxer/SyntaxAnalyzer.cpp src/module/analyzer/synaxer/SyntaxAnalyzer.h src/models/codes/Blocks.h)
