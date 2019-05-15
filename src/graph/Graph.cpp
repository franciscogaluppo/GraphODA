#include "Graph.hpp"

Graph::Graph() {
	n = 0, m = 0;
	weighted = 0;
}

Graph::Graph(int n_) {
	n = n_;
	m = 0;
	weighted = 0;
	adj.resize(n);
	for (int i = 0; i < n; i++) label.push_back(to_string(i));
}

Graph::Graph(int n_, vector<string> &label_) {
	n = n_;
	m = 0;
	weighted = 0;
	adj.resize(n);
	for (int i = 0; i < n; i++) {
		if (i >= label_.size()) label.push_back(to_string(i));
		else label.push_back(label_[i]);
	}
}

int Graph::getN() {
	return n;	
}

int Graph::getM() {
	return m;	
}

bool Graph::isWeighted() {
	return weighted;
}

// O(n+m)
vector<vector<pair<int, int> > > Graph::getAdj() {
	return adj;
}

// O(n+m)
vector<pair<int, int> > Graph::getEdges() {
	vector<pair<int, int> > edg;
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		edg.push_back({i, j.first});
	return edg;
}

vector<int> Graph::getPesos() {
	vector<int> pes;
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		pes.push_back(j.second);
	return pes;
}

// O(n^2)
vector<vector<int> > Graph::getMatrix() {
	vector<vector<int> > matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		matrix[i][j.first] = 1;
	return matrix;
}

// O(n^2)
vector<vector<int> > Graph::getSimMatrix() {
	vector<vector<int> > matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) for (auto j : adj[i])
		matrix[i][j.first] = matrix[j.first][i] = 1;
	return matrix;
}

// O(1)
void Graph::addEdge(int i, int j) {
	if (i < 0 or j < 0 or i == j or i >= n or j >= n) {
		// TODO: Erro direito
		cout << "ERRO: aresta zoada" << endl;
		return;
	}
	adj[i].push_back({j, 1});
	m++;
}

// O(1)
void Graph::addEdge(int i, int j, int k) {
	if (i < 0 or j < 0 or i == j or i >= n or j >= n) {
		// TODO: Erro direito
		cout << "ERRO: aresta zoada" << endl;
		return;
	}
	adj[i].push_back({j, k});
	if (k != 1) weighted = true;
	m++;
}
