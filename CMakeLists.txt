cmake_minimum_required(VERSION 3.17)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(compiler src/main.cpp src/module/analyzer/LexAnalyzer.cpp src/module/analyzer/LexAnalyzer.h src/models/analyzer/impl/Token.cpp src/models/analyzer/headers/Token.h src/models/analyzer/impl/Constant.cpp src/models/analyzer/headers/Constant.h src/module/io/IOModule.cpp src/module/io/IOModule.h src/models/Codes.h src/models/io/impl/Error.cpp src/models/io/headers/Error.h src/models/io/impl/TextPosition.cpp src/models/io/headers/TextPosition.h)
