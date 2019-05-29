#include "Chordal.hpp"

Chordal::Chordal() : GraphGen() {}

Chordal::Chordal(int n) : GraphGen(n) {}

Chordal::Chordal(GraphGen& G) {
	if (!G.isChordal()) throw ChordalConstructorException();

	n = G.getN();
	m = G.getM();
	label = G.label;
	adj = G.getAdj();
	simAdj = G.getSimAdj();
}
