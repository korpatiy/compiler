cmake_minimum_required(VERSION 3.17)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(compiler src/main.cpp src/module/analyzer/LexAnalyzer.cpp src/module/analyzer/LexAnalyzer.h src/models/Token.cpp src/models/Token.h src/models/Constant.cpp src/models/Constant.h)
