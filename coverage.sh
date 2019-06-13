set -e
mkdir -p coverage build
cd build
cmake .. -DCMAKE_CXX_FLAGS="--coverage"
make tests
./tests/tests
find CMakeFiles/common.dir CMakeFiles/graphODA.dir -name "*.cpp.gcno" | xargs gcov
gcovr -g -k -r ../src/ . --html --html-details -o ../coverage/index.html