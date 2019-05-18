#include "DSU.hpp"

DSU::DSU() {
	n = 0;
}

DSU::DSU(int n_) {
	n = n_;
	v.resize(n);
	sz = vector<int>(n, 1);
	for (int i = 0; i < n; i++) v[i] = i;
}

int DSU::find(int k) {
	if (k < 0 or k >= n) {
		// TODO: Erro direito
		cout << "Erro: valor zoado no DSU-find" << endl;
		return -1;
	}
	return v[k] == k ? k : v[k] = find(v[k]);
}

void DSU::une(int a, int b) {
	if (a < 0 or a >= n or b < 0 or b >= n) {
		// TODO: Erro direito
		cout << "Erro: valor zoado no DSU-une" << endl;
		return;
	}
	a = find(a), b = find(b);
	if (sz[a] > sz[b]) swap(a, b);
	v[a] = b;
	sz[b] += sz[a];
}
