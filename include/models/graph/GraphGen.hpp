#ifndef GRAPHGENH
#define GRAPHGENH

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class GraphGen {
 public:
  vector<string> label;

  GraphGen();
  GraphGen(int);
  GraphGen(int, vector<string> &);

  int getN();
  int getM();
  bool isWeighted();
  vector<vector<pair<int, int>>> getAdj();
  vector<pair<int, int>> getEdges();
  vector<int> getPesos();
  vector<vector<int>> getMatrix();
  vector<vector<int>> getSimMatrix();

 protected:
  int n, m;
  vector<vector<pair<int, int>>> adj;
  bool weighted;
};

#endif
