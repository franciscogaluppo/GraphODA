#ifndef GRAPH
#define GRAPH

#include "Bipartite.hpp"
#include "Chordal.hpp"
#include "Dag.hpp"
#include "GraphGen.hpp"
#include "Tree.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Graph : public GraphGen {
 public:
  Graph();
  Graph(int);
  Graph(int, vector<string> &);
  Graph(Bipartite);
  Graph(Chordal);
  Graph(Dag);
  Graph(Tree);

  void addEdge(int, int);
  void addEdge(int, int, int);

  Tree mst();
};

#endif
