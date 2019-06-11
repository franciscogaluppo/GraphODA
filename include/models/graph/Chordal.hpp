#ifndef CHORDALH
#define CHORDALH

#include "GraphGen.hpp"

/// @file
///
/// Classe para grafos cordais.
class Chordal : public GraphGen {
   public:
	Chordal();
	Chordal(int);
	Chordal(GraphGen &);

	// Algoritmos
	/// Cria uma ordem de eliminação perfeita dos vértices.
	/// Complexidade: O(nlog(n))
	vector<int> perfectEliminationOrdering();

	/// Algoritmo de coloração para grafos cordais.
	/// Complexidade: O(nlog() + m)
	vector<int> coloring() override;

	/// Calcula o número cromático do grafo
	/// Complexidade: O(nlog() + m)
	int chromaticNumber();

	/// Calcula o tamanho da maior clique do grafo
	/// Complexidade: O(nlog() + m)
	int maxClique();
};

class ChordalConstructorException : public GraphException {
   public:
	ChordalConstructorException() {}
	const char *what() const throw() {
		return "constructor parameter is not chordal";
	}
};

#endif
