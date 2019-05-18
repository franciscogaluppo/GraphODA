#include "GraphGen.hpp"

GraphGen::GraphGen() {
	n = 0, m = 0;
	weighted = false;
}

GraphGen::GraphGen(int n_) {
	n = n_;
	m = 0;
	weighted = false;
	adj.resize(n);
	for (int i = 0; i < n; i++) label.push_back(to_string(i));
}

GraphGen::GraphGen(int n_, vector<string> &label_) {
	n = n_;
	m = 0;
	weighted = false;
	adj.resize(n);
	for (int i = 0; i < n; i++) {
		if (i >= label_.size()) label.push_back(to_string(i));
		else label.push_back(label_[i]);
	}
}

int GraphGen::getN() {
	return n;
}

int GraphGen::getM() {
	return m;	
}

bool GraphGen::isWeighted() {
	return weighted;	
}

// O(n+m)
vector<vector<pair<int, int> > > GraphGen::getAdj() {
	return adj;	
}

// O(n+m)
vector<pair<int, int> > GraphGen::getEdges() {
	vector<pair<int, int> > edg;
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		edg.push_back({i, j.first});
	return edg;
}

vector<int> GraphGen::getPesos() {
	vector<int> pes;
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		pes.push_back(j.second);
	return pes;
}

// O(n^2)
vector<vector<int> > GraphGen::getMatrix() {
	vector<vector<int> > matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		matrix[i][j.first] = 1;
	return matrix;
}

// O(n^2)
vector<vector<int> > GraphGen::getSimMatrix() {
	vector<vector<int> > matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		matrix[i][j.first] = matrix[j.first][i] = 1;
	return matrix;
}
