#include "Graph.hpp"

Graph::Graph() {
	n = 0, m = 0;
}

Graph::Graph(int n_) {
	n = n_;
	m = 0;
	adj.resize(n);
	for (int i = 0; i < n; i++) label.push_back(to_string(i));
}

Graph::Graph(int n_, vector<string> &label_) {
	n = n_;
	m = 0;
	adj.resize(n);
	for (int i = 0; i < n; i++) {
		if (i >= label_.size()) label.push_back(to_string(i));
		else label.push_back(label_[i]);
	}
}

// O(1)
void Graph::addEdge(int i, int j) {
	if (i < 0 or j < 0 or i == j or i >= n or j >= n) {
		// TODO: Erro direito
		cout << "ERRO: aresta zoada" << endl;
		return;
	}
	adj[i].push_back(j);
	edges.push_back({i, j});
	m++;
}
