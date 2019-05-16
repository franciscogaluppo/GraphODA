#include "Tree.hpp"

Tree::Tree() : Chordal() {}

Tree::Tree(int n) : Chordal(n) {}

// O(m log(m))
Tree mst(Graph &G) {
	auto ar = G.getEdges();
	auto pesos = G.getPesos();
	vector<pair<int, pair<int, int> > > v;
	for (int i = 0; i < G.getM(); i++)
		v.push_back({pesos[i], ar[i]});
	sort(v.begin(), v.end());
	Tree T(G.getN());
	DSU dsu(G.getN());
	for (int i = 0; i < G.getM(); i++) {
		int a = v[i].second.first, b = v[i].second.second;
		if (dsu.find(a) != dsu.find(b)) {
			dsu.une(a, b);
			T.addEdge(a, b, v[i].first);
		}
	}
	return T;
}
