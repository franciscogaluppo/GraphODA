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
	simAdj.resize(n);
	for (int i = 0; i < n; i++) label.push_back(to_string(i));
}

GraphGen::GraphGen(int n_, vector<string> &label_) {
	n = n_;
	m = 0;
	weighted = false;
	adj.resize(n);
	simAdj.resize(n);
	for (int i = 0; i < n; i++) {
		if (i >= label_.size())
			label.push_back(to_string(i));
		else
			label.push_back(label_[i]);
	}
}

int GraphGen::getN() { return n; }

int GraphGen::getM() { return m; }

bool GraphGen::isWeighted() { return weighted; }

// O(n+m)
vector<vector<pair<int, int>>> GraphGen::getAdj() { return adj; }

vector<vector<pair<int, int>>> GraphGen::getSimAdj() { return simAdj; }

// O(n+m)
vector<pair<int, int>> GraphGen::getEdges() {
	vector<pair<int, int>> edg;
	for (int i = 0; i < n; i++)
		for (auto j : adj[i]) edg.push_back({i, j.first});
	return edg;
}

vector<int> GraphGen::getPesos() {
	vector<int> pes;
	for (int i = 0; i < n; i++)
		for (auto j : adj[i]) pes.push_back(j.second);
	return pes;
}

// O(n^2)
vector<vector<int>> GraphGen::getMatrix() {
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (auto j : adj[i]) matrix[i][j.first] = 1;
	return matrix;
}

// O(n^2)
vector<vector<int>> GraphGen::getSimMatrix() {
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (auto j : adj[i]) matrix[i][j.first] = matrix[j.first][i] = 1;
	return matrix;
}

bool GraphGen::dfsCheckBipartite(int i, int c, vector<int>& cor) {
	cor[i] = c;
	for (auto j : simAdj[i]) {
		if (cor[j.first] == c) return false;
		if (cor[j.first] == -1 and !dfsCheckBipartite(j.first, !c, cor))
			return false;
	}
	return true;
}

// O(n+m)
bool GraphGen::isBipartite() {
	vector<int> cor(n, -1);
	for (int i = 0; i < n; i++)
		if (cor[i] == -1 and !dfsCheckBipartite(i, 0, cor)) return false;
	return true;
}

bool GraphGen::isChordal() {
	return false;	
}

bool GraphGen::dfsCheckDag(int i, vector<int>& vis) {
	vis[i] = 1;
	for (auto j : adj[i]) {
		if (vis[j.first] == 1) return false;
		if (!vis[j.first] and !dfsCheckDag(j.first, vis)) return false;
	}
	vis[i] = 2;
	return true;
}

// O(n+m)
bool GraphGen::isDag() {
	vector<int> vis(n, 0);
	for (int i = 0; i < n; i++) if (!vis[i] and !dfsCheckDag(i, vis)) return false;
	return true;
}

bool GraphGen::dfsCheckTree(int i, int last, vector<int>& vis) {
	vis[i] = 1;
	for (auto j : simAdj[i]) {
		if (j.first != last and vis[j.first] == 1) return false;
		if (!vis[j.first] and !dfsCheckTree(j.first, i, vis)) return false;
	}
	vis[i] = 2;
	return true;
}

// O(n+m)
bool GraphGen::isTree() {
	vector<int> vis(n, 0);
	for (int i = 0; i < n; i++) if (!vis[i] and !dfsCheckTree(i, i, vis)) return false;
	return true;
}
