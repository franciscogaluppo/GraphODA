#ifndef GRAPHGENH
#define GRAPHGENH

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <queue>
using namespace std;

class GraphGen {
	public:
		vector<string> label;

		GraphGen();
		GraphGen(int);
		GraphGen(int, vector<string> &);

		// gets
		int getN();
		int getM();
		vector<vector<pair<int, int>>> getAdj();
		vector<vector<pair<int, int>>> getSimAdj();
		vector<pair<int, int>> getEdges();
		vector<int> getPesos();
		vector<vector<int>> getMatrix();
		vector<vector<int>> getSimMatrix();

		// auxiliares
		bool isWeighted();
		bool hasNegativeWeight();
		bool reaches(int, int);

		// reconhecedores
		bool isBipartite();
		bool isChordal();
		bool isDag();
		bool isTree();

		// algoritmos
		vector<int> scc();
		long long shortestPath(int, int);

	protected:
		int n, m;
		vector<vector<pair<int, int>>> adj;
		vector<vector<pair<int, int>>> simAdj;

	private:
		// auxiliares
		bool dfsReaches(vector<bool>&, int, int);
		bool dfsCheckBipartite(int, int, vector<int>&);
		bool dfsCheckDag(int, vector<int>&);
		bool dfsCheckTree(int, int, vector<int>&);
		int dfsScc(vector<int>&, vector<int>&, vector<int>&, int&, int&, int);

		// algoritmos
		long long shortestPathBFS(int, int);
		long long dijkstra(int, int);
		long long bellmanFord(int, int);
};

class GraphException : public exception {
	public:
		GraphException() {}
		const char *what() const throw () { return "Graph Exception"; }
};

class GraphNoPathException : public GraphException {
	public:
		GraphNoPathException(int a_, int b_) : a(a_), b(b_) {}
		const char *what() const throw () { return "no path"; }
		pair<int, int> get() { return make_pair(a, b); }

	private:
		int a, b;
};

class GraphNegativeCycleException : public GraphException {
	public:
		GraphNegativeCycleException() {}
		const char *what() const throw () { return "negative cycle found; shortest path is undefined"; }
};

#endif
