#include "GraphGen.hpp"

GraphGen::GraphGen() { n = 0, m = 0; }

GraphGen::GraphGen(int n_) {
	n = n_;
	m = 0;
	adj.resize(n);
	simAdj.resize(n);
	for (int i = 0; i < n; i++) label.push_back(to_string(i));
}

GraphGen::GraphGen(int n_, vector<string>& label_) {
	n = n_;
	m = 0;
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

// O(n+m)
bool GraphGen::isWeighted() {
	for (int i = 0; i < n; i++)
		for (auto j : adj[i])
			if (j.second != 1) return true;
	return false;
}

// O(n+m)
bool GraphGen::hasNegativeWeight() {
	for (int i = 0; i < n; i++)
		for (auto j : adj[i])
			if (j.second < 0) return true;
	return false;
}

bool GraphGen::dfsReaches(vector<bool>& vis, int a, int b) {
	vis[a] = true;
	if (a == b) return true;

	for (auto i : adj[a])
		if (!vis[i.first] and dfsReaches(vis, i.first, b)) return true;
	return false;
}

bool GraphGen::reaches(int a, int b) {
	vector<bool> vis(n, false);
	return dfsReaches(vis, a, b);
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

pair<vector<int>, vector<int>> GraphGen::maximumCardinalitySearch() {
	vector<set<int>> Set(n);
	vector<int> size(n, 0);
	vector<int> alpha(n);
	vector<int> alphaInv(n);
	vector<bool> visitado(n, 0);

	for (int k = 0; k < n; k++) Set[0].insert(k);

	// Maximum Cardinality Search
	for (int i = n - 1, j = 0; i >= 0; i--) {
		int v = *Set[j].begin();
		Set[j].erase(v);
		j++;

		alpha[v] = i;
		alphaInv[i] = v;
		size[v] = -1;

		fill(visitado.begin(), visitado.end(), false);
		for (auto u : simAdj[v]) {
			int w = u.first;
			if (visitado[w] || size[w] < 0) continue;

			visitado[w] = true;
			Set[size[w]].erase(w);
			size[w]++;
			Set[size[w]].insert(w);
		}

		while (j > 0 && Set[j].empty()) j--;
	}

	return make_pair(alpha, alphaInv);
}

bool GraphGen::checkOrdering(vector<int> ordering) {
	if (ordering.size() != n) return false;

	vector<bool> checker(n, false);
	int count = 0;

	for (auto x : ordering) {
		if (x >= n || x < 0) return false;

		if (!checker[x]) {
			checker[x] = true;
			count++;
		}
	}

	return count == n;
}

bool GraphGen::zeroFillIn(pair<vector<int>, vector<int>> parAlpha) {
	vector<int> alpha = parAlpha.first;
	vector<int> alphaInv = parAlpha.second;

	if (!checkOrdering(alpha)) throw GraphOrderingException();
	if (!checkOrdering(alphaInv)) throw GraphOrderingException();

	vector<int> f(n);
	vector<int> index(n);
	vector<bool> visitado(n, 0);

	// Zero Fill-in
	for (int i = 0; i < n; i++) {
		int w = alphaInv[i];
		f[w] = w;
		index[w] = i;

		fill(visitado.begin(), visitado.end(), false);
		for (auto u : simAdj[w]) {
			int v = u.first;
			if (visitado[v]) continue;

			if (alpha[v] >= i) continue;

			visitado[v] = true;
			index[v] = i;

			if (f[v] == v) f[v] = w;
		}

		fill(visitado.begin(), visitado.end(), false);
		for (auto u : simAdj[w]) {
			int v = u.first;
			if (visitado[v]) continue;

			if (alpha[v] >= i) continue;

			visitado[v] = true;
			if (index[f[v]] < i) return false;
		}
	}
	return true;
}

bool GraphGen::isChordal() { return zeroFillIn(maximumCardinalitySearch()); }

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
	for (int i = 0; i < n; i++)
		if (!vis[i] and !dfsCheckDag(i, vis)) return false;
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
	for (int i = 0; i < n; i++)
		if (!vis[i] and !dfsCheckTree(i, i, vis)) return false;
	return true;
}

// algoritmo de Tarjan para SCC
int GraphGen::dfsScc(vector<int>& comp, vector<int>& vis, vector<int>& id,
					 int& t, int& c, int k) {
	static stack<int> s;

	int lo = id[k] = t++;
	s.push(k);
	vis[k] = 2;

	for (int i = 0; i < adj[k].size(); i++) {
		if (!vis[adj[k][i].first])
			lo = min(lo, dfsScc(comp, vis, id, t, c, adj[k][i].first));
		else if (vis[adj[k][i].first] == 2)
			lo = min(lo, id[adj[k][i].first]);
	}
	if (lo == id[k])
		while (1) {
			int u = s.top();
			s.pop();
			vis[u] = 1;
			comp[u] = c;
			if (u == k) {
				c++;
				break;
			}
		}
	return lo;
}

// O(n+m)
vector<int> GraphGen::scc() {
	vector<int> vis(n, 0), comp(n), id(n);
	int t = -1, c = 0;
	for (int i = 0; i < n; i++)
		if (!vis[i]) dfsScc(comp, vis, id, ++t, c, i);
	return comp;
}

// O(n+m)
long long GraphGen::shortestPathBFS(int a, int b) {
	vector<bool> vis(n, 0);
	queue<pair<int, int>> q;
	vis[a] = true;
	q.push({a, 0});

	while (q.size()) {
		int u = q.front().first, d = q.front().second;
		q.pop();

		if (u == b) return d;
		for (auto i : adj[u])
			if (!vis[i.first]) {
				q.push({i.first, d + 1});
				vis[i.first] = true;
			}
	}
	throw GraphNoPathException(a, b);
}

// O(m log(n))
long long GraphGen::dijkstra(int a, int b) {
	vector<long long> d(n, 0x3f3f3f3f3f3f3f3fll);
	priority_queue<pair<long long, int>, vector<pair<long long, int>>,
				   greater<pair<long long, int>>>
		q;
	d[a] = 0;
	q.push({0, a});

	while (q.size()) {
		int u = q.top().second;
		long long dist = q.top().first;
		q.pop();
		if (dist > d[u]) continue;

		for (auto i : adj[u]) {
			int v = i.first, w = i.second;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push({d[v], v});
			}
		}
	}
	return d[b];
}

long long GraphGen::bellmanFord(int a, int b) {
	vector<long long> d(n, 0x3f3f3f3f3f3f3f3fll);
	d[a] = 0;
	auto edg = this->getEdges();
	auto pesos = this->getPesos();

	for (int i = 0; i <= n; i++)
		for (int j = 0; j < m; j++) {
			if (d[edg[j].first] + pesos[j] < d[edg[j].second]) {
				if (i == n) throw GraphNegativeCycleException();

				d[edg[j].second] = d[edg[j].first] + pesos[j];
			}
		}

	return d[b];
}

long long GraphGen::shortestPath(int a, int b) {
	if (!this->reaches(a, b)) throw GraphNoPathException(a, b);

	if (this->hasNegativeWeight()) return bellmanFord(a, b);
	if (!this->isWeighted()) return shortestPathBFS(a, b);
	return dijkstra(a, b);
}

// Recebe uma ordem dos vértices e colore
vector<int> GraphGen::greedyColoring(vector<int> alpha) {
	if (!checkOrdering(alpha)) throw GraphOrderingException();

	vector<int> colors(n, 0);
	vector<int> vizinhanca;
	vector<bool> visitado(n, false);

	// Itera pela ordenação de trás para frente
	for (int i = n - 1; i >= 0; i--) {
		int max = 0;
		vizinhanca.clear();
		fill(visitado.begin(), visitado.end(), false);

		// Vê quais cores dos vizinhos
		for (auto u : simAdj[alpha[i]]) {
			int w = u.first;
			if (visitado[w]) continue;

			visitado[w] = true;
			if (colors[w]) vizinhanca.push_back(colors[w]);
			max++;
		}

		// Marca as cores usadas
		vector<int> possiveis(max + 1, 0);
		for (auto c : vizinhanca)
			if (c <= max) possiveis[c - 1]++;

		// Seleciona a menor cor não usada
		for (int j = 0; j <= max; j++)
			if (possiveis[j] == 0) {
				colors[alpha[i]] = j + 1;
				break;
			}

		if (!max) colors[alpha[i]] = 1;
	}

	return colors;
}

vector<int> GraphGen::greedyColoring() {
	vector<int> ordem(n);
	iota(ordem.begin(), ordem.end(), 0);
	return greedyColoring(ordem);
}

void GraphGen::dfsArt(vector<bool> &vis, vector<int> &in, vector<int> &low, vector<int> &parent, vector<bool> &isArt, int v, int p, int &d) {
	parent[v] = p;
	low[v] = in[v] = d++;
	isArt[v] = false;
	for (auto j : simAdj[v]) {
		if (j.first == p) continue;
		if (in[j.first] == -1) {
			dfsArt(vis, in, low, parent, isArt, j.first, v, d);
			if (low[j.first] >= in[v]) isArt[v] = true;
			low[v] = min(low[v], low[j.first]);
		} else low[v] = min(low[v], in[j.first]);
	}
	if (p == -1) {
		isArt[v] = false;
		int k = 0;
		for (auto j : simAdj[v]) if (!vis[j.first]) {
			vis[j.first] = true;
			k += (parent[j.first] == v);
		}
		if (k > 1) isArt[v] = true;
	}
}

vector<bool> GraphGen::artPoints() {
	vector<bool> isArt(n), vis(n, false);
	vector<int> in(n, -1), low(n), parent(n);
	int d = -1;
	for (int i = 0; i < n; i++) if (in[i] == -1)
		dfsArt(vis, in, low, parent, isArt, i, -1, ++d);
	return isArt;
}

// TODO
vector<int> GraphGen::coloring() { return vector<int>(); }
