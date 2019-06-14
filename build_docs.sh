#!/usr/bin/env bash
set -e

# Gera documentação do código
doxygen Doxyfile

# Gera relatório de cobertura de testes
mkdir -p docs/coverage build
cd build
cmake .. -DCMAKE_CXX_FLAGS="--coverage"
make tests
find CMakeFiles/common.dir CMakeFiles/graphODA.dir -name "*.cpp.gcno" | xargs gcov
gcovr -g -k -r ../src/ . --html --html-details -o ../docs/coverage/index.html