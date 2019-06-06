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

vector<int> Chordal::perfectEliminationOrdering()
{
	return maximumCardinalitySearch().second;
}

vector<int> Chordal::coloring()
{
	return greedyColoring(perfectEliminationOrdering());
}

int Chordal::chromaticNumber()
{
	vector<int> cores = coloring();
	int maior = 0;
	for(auto c: cores)
		maior = (c > maior? c: maior);
	return maior;
}
