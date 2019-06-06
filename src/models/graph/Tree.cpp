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

