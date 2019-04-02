#include "Graph.hpp"

Graph::Graph(int n) {
	this->n = n;
	m = 0;
	adj.resize(n);
	for (int i = 0; i < n; i++) label.push_back(to_string(i));
}

Graph::Graph(int n, vector<string> &label) {
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
	edges.push_back({i, j});
	m++;
}

bool tenta(Graph *G, vector<int> &ans, int k, int p) {
	if (p == G->n) {
		for (auto i : G->edges) if (ans[i.first] == ans[i.second]) return 0;
		return 1;
	}
	for (int i = 1; i <= k; i++) {
		ans[p] = i;
		if (tenta(G, ans, k, p+1)) return 1;
	}
	return 0;
}

vector<int> Graph::getColoring() {
	vector<int> ans(n);
	for (int k = 1; ; k++) if (tenta(this, ans, k, 0)) return ans;
}
