#include "Graph.hpp"

Graph::Graph() : GraphGen() {}

Graph::Graph(int n_) : GraphGen(n_) {}

Graph::Graph(int n_, vector<string> &label_) : GraphGen(n_, label_) {}

Graph::Graph(GraphGen &G) {
	n = G.getN();
	m = G.getM();
	label = G.label;
	adj = G.getAdj();
	simAdj = G.getSimAdj();
}

// O(1)
void Graph::addEdge(int i, int j) {
	if (i < 0 or i >= n) throw GraphVertexOutOfBoundsException(i);
	if (j < 0 or j >= n) throw GraphVertexOutOfBoundsException(j);
	if (i == j) throw GraphSelfLoopException(i);

	adj[i].push_back({j, 1});
	simAdj[i].push_back({j, 1});
	simAdj[j].push_back({i, 1});
	m++;
}

// O(1)
void Graph::addEdge(int i, int j, int k) {
	if (i < 0 or i >= n) throw GraphVertexOutOfBoundsException(i);
	if (j < 0 or j >= n) throw GraphVertexOutOfBoundsException(j);
	if (i == j) throw GraphSelfLoopException(i);

	adj[i].push_back({j, k});
	simAdj[i].push_back({j, k});
	simAdj[j].push_back({i, k});
	m++;
}

// O(m log(m))
Tree Graph::mst() {
	auto ar = this->getEdges();
	auto pesos = this->getPesos();

	vector<pair<int, pair<int, int>>> v;
	for (int i = 0; i < m; i++) v.push_back({pesos[i], ar[i]});
	sort(v.begin(), v.end());
	Graph T(n, this->label);
	DSU dsu(n);
	for (auto i : v) {
		int a = i.second.first, b = i.second.second;
		if (dsu.find(a) != dsu.find(b)) {
			dsu.une(a, b);
			T.addEdge(a, b, i.first);
		}
	}
	return Tree(T);
}
