#include "Dag.hpp"

Dag::Dag() : GraphGen() {}

Dag::Dag(int n) : GraphGen(n) {}

Dag::Dag(GraphGen& G) {
	if (!G.isDag()) throw DagConstructorException();

	n = G.getN();
	m = G.getM();
	label = G.label;
	adj = G.getAdj();
	simAdj = G.getSimAdj();
}
