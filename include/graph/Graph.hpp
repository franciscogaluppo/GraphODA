#ifndef GRAPH
#define GRAPH

#include "GraphGen.hpp"
#include "Bipartite.hpp"
#include "Chordal.hpp"
#include "Dag.hpp"
#include "Tree.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Graph : public GraphGen {
	public:
		Graph();
		Graph(int);
		Graph(int, vector<string>&);
		Graph(Bipartite);
		Graph(Chordal);
		Graph(Dag);
		Graph(Tree);

		void addEdge(int, int);
		void addEdge(int, int, int);

		Tree mst();
};

#endif
