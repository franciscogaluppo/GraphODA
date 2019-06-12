#include "Tree.hpp"

Tree::Tree() : Chordal() {}

Tree::Tree(int n) : Chordal(n) {}

Tree::Tree(GraphGen& G) {
	if (!G.isTree()) throw TreeConstructorException();

	n = G.getN();
	m = G.getM();
	label = G.label;
	adj = G.getAdj();
	simAdj = G.getSimAdj();
}

pair<int, vector<int> > Tree::bfsCenter(int k) {
	queue<int> q;
	q.push(k);
	vector<bool> vis(n, false);
	vis[k] = 1;
	vector<int> d(n);
	d[k] = 0;
	int last = k, lastD = 0;

	while (q.size()) {
		int u = q.front();
		q.pop();
		for (auto i : simAdj[u])
			if (!vis[i.first]) {
				vis[i.first] = 1;
				q.push(i.first);
				d[i.first] = d[u] + i.second;
				if (d[i.first] > lastD) {
					lastD = d[i.first];
					last = i.first;
				}
			}
	}
	return make_pair(last, d);
}

int Tree::center() {
	auto a = bfsCenter(0);
	auto b = bfsCenter(a.first);
	auto c = bfsCenter(b.first);
	int ans, mi = 0x3f3f3f3f;
	for (int i = 0; i < n; i++)
		if (max(b.second[i], c.second[i]) < mi) {
			mi = max(b.second[i], c.second[i]);
			ans = i;
		}
	return ans;
}

int Tree::diameter() {
	auto a = bfsCenter(0);
	auto b = bfsCenter(a.first);
	auto c = bfsCenter(b.first);
	return c.second[a.first];
}
