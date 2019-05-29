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
};

class GraphVertexOutOfBoundsException : public GraphException {
	public:
		GraphVertexOutOfBoundsException(int n_) : n(n_) {}
		const char *what() const throw () {
			return "vertex out of bounds";
		}
		int get() { return n; }

	private:
		int n;
};

class GraphSelfLoopException : public GraphException {
	public:
		GraphSelfLoopException(int n_) : n(n_) {}
		const char *what() const throw () {
			return "self loop not allowed";
		}
		int get() { return n; }

	private:
		int n;
};

#endif
