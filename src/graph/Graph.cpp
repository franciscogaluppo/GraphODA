#include "Graph.hpp"

Graph::Graph() : GraphGen() {}

Graph::Graph(int n_) : GraphGen(n_) {}

Graph::Graph(int n_, vector<string> &label_) : GraphGen(n_, label_) {}

Graph::Graph(Bipartite B) {
	n = B.getN();
	m = B.getM();
	label = B.label;
	adj = B.getAdj();
	weighted = B.isWeighted();
}

Graph::Graph(Chordal C) {
	n = C.getN();
	m = C.getM();
	label = C.label;
	adj = C.getAdj();
	weighted = C.isWeighted();
}

Graph::Graph(Dag D) {
	n = D.getN();
	m = D.getM();
	label = D.label;
	adj = D.getAdj();
	weighted = D.isWeighted();
}

Graph::Graph(Tree T) {
	n = T.getN();
	m = T.getM();
	label = T.label;
	adj = T.getAdj();
	weighted = T.isWeighted();
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

// O(m log(m))
Tree Graph::mst() {
	auto ar = this->getEdges();
	auto pesos = this->getPesos();
	vector<pair<int, pair<int, int> > > v;
	for (int i = 0; i < m; i++)
		v.push_back({pesos[i], ar[i]});
	sort(v.begin(), v.end());
	Tree T(n);
	for (auto i : v) T.addEdge(i.second.first, i.second.second, i.first);
	return T;
}
