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
		vector<vector<pair<int, int>>> getSimAdj();
		vector<pair<int, int>> getEdges();
		vector<int> getPesos();
		vector<vector<int>> getMatrix();
		vector<vector<int>> getSimMatrix();

		bool isBipartite();
		bool isChordal();
		bool isDag();
		bool isTree();

	protected:
		int n, m;
		vector<vector<pair<int, int>>> adj;
		vector<vector<pair<int, int>>> simAdj;
		bool weighted;

	private:
		bool dfsCheckBipartite(int, int, vector<int>&);
		bool dfsCheckDag(int, vector<int>&);
		bool dfsCheckTree(int, int, vector<int>&);
};

#endif
