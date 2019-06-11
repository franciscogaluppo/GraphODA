#include "Dag.hpp"

Dag::Dag() : GraphGen() {}

Dag::Dag(int n) : GraphGen(n) {}

Dag::Dag(GraphGen &G) {
	if (!G.isDag()) throw DagConstructorException();

	n = G.getN();
	m = G.getM();
	label = G.label;
	adj = G.getAdj();
	simAdj = G.getSimAdj();
}

void Dag::topoSortDfs(vector<bool> &vis, vector<int> &topo, int v) {
	vis[v] = true;
	for (auto i : adj[v])
		if (!vis[i.first]) topoSortDfs(vis, topo, i.first);
	topo.push_back(v);
}

vector<int> Dag::topoSort() {
	vector<bool> vis(n, false);
	vector<int> topo;
	for (int i = 0; i < n; i++)
		if (!vis[i]) topoSortDfs(vis, topo, i);
	reverse(topo.begin(), topo.end());
	return topo;
}
