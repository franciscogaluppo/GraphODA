#include "Graph.hpp"

Graph::Graph(int n) {
	this->n = n;
	m = 0;
	adj.resize(n);
	for (int i = 0; i < n; i++) label.push_back(to_string(i));
}

Graph::Graph(int n, vector<string> label) {
	this->n = n;
	m = 0;
	adj.resize(n);
	for (int i = 0; i < n; i++) {
		if (i >= label.size()) this->label.push_back(to_string(i));
		else this->label.push_back(label[i]);
	}
}

void Graph::addEdge(int i, int j) {
	if (i >= n or j >= n) {
		// TODO: Erro direito
		cout << "ERRO: aresta zoada" << endl;
		return;
	}
	adj[i].push_back(j);
	adj[j].push_back(i);
	edges.push_back({i, j});
	m++;
}
