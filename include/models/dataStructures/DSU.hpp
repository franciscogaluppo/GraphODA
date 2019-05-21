#ifndef DSUH
#define DSUH

#include <iostream>
#include <vector>
using namespace std;

class DSU {
 public:
  DSU();
  DSU(int);
  int find(int);
  void une(int, int);

 private:
  int n;
  vector<int> v;
  vector<int> sz;
};

#endif
