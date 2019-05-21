#include "Tree.hpp"

Tree::Tree() : Chordal() {}

Tree::Tree(int n) : Chordal(n) { dsu = DSU(n); }

void Tree::addEdge(int i, int j) {
  if (i < 0 or j < 0 or i == j or i >= n or j >= n) {
    // TODO: Erro direito
    cout << "Erro: aresta zoada" << endl;
    return;
  }
  if (dsu.find(i) == dsu.find(j)) return;
  dsu.une(i, j);
  adj[i].push_back({j, 1});
  m++;
}

void Tree::addEdge(int i, int j, int k) {
  if (i < 0 or j < 0 or i == j or i >= n or j >= n) {
    // TODO: Erro direito
    cout << "Erro: aresta zoada" << endl;
    return;
  }
  if (dsu.find(i) == dsu.find(j)) return;
  dsu.une(i, j);
  adj[i].push_back({j, k});
  if (k != 1) weighted = true;
  m++;
}
