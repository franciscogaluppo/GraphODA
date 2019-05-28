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
		bool isWeighted();
		vector<vector<pair<int, int>>> getAdj();
		vector<vector<pair<int, int>>> getSimAdj();
		vector<pair<int, int>> getEdges();
		vector<int> getPesos();
		vector<vector<int>> getMatrix();
		vector<vector<int>> getSimMatrix();

		// auxiliares
		bool reaches(int, int);

		// reconhecedores
		bool isBipartite();
		bool isChordal();
		bool isDag();
		bool isTree();

		// algoritmos
		vector<int> scc();
		long long shortestPathBFS(int, int);
		long long dijkstra(int, int);
		long long shortestPath(int, int);

	protected:
		int n, m;
		vector<vector<pair<int, int>>> adj;
		vector<vector<pair<int, int>>> simAdj;
		bool weighted;

	private:
		bool dfsReaches(vector<bool>&, int, int);
		bool dfsCheckBipartite(int, int, vector<int>&);
		bool dfsCheckDag(int, vector<int>&);
		bool dfsCheckTree(int, int, vector<int>&);
		int dfsScc(vector<int>&, vector<int>&, vector<int>&, int&, int&, int);
};

#endif
