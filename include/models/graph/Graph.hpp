#ifndef GRAPH
#define GRAPH

#include "Bipartite.hpp"
#include "Chordal.hpp"
#include "Dag.hpp"
#include "DSU.hpp"
#include "GraphGen.hpp"
#include "Tree.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <string>
using namespace std;

class Graph : public GraphGen {
	public:
		Graph();
		Graph(int);
		Graph(int, vector<string> &);
		Graph(GraphGen&);

		void addEdge(int, int);
		void addEdge(int, int, int);

		Tree mst();
		vector<bool> mstEdges();
};

class GraphVertexOutOfBoundsException : public GraphException {
	public:
		GraphVertexOutOfBoundsException(int n) {
			msg = "vertex out of bounds: "+to_string(n);	
		}
		const char *what() const throw () { return msg.c_str(); }

	private:
		string msg;
};

class GraphSelfLoopException : public GraphException {
	public:
		GraphSelfLoopException(int n) {
			msg = "self loop not allowed (at vertex "+to_string(n)+")";
		}
		const char *what() const throw () { return msg.c_str(); }

	private:
		string msg;
};

#endif
