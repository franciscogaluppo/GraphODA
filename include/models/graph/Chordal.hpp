#ifndef CHORDALH
#define CHORDALH

#include "GraphGen.hpp"

///
/// @file

///
/// Classe para grafos cordais.
class Chordal : public GraphGen {
  public:
	///
	/// Construtor de grafos cordais vazios.
	Chordal();

	///
	/// Construtor de grafos cordais por número de vértices.
	Chordal(int);

	///
	/// Construtor de grafos cordais por GraphGen
	Chordal(GraphGen &);

	// Algoritmos
	/// Cria uma ordem de eliminação perfeita dos vértices.
	///
	/// Complexidade: O(nlog(n))
	vector<int> perfectEliminationOrdering();

	/// Algoritmo de coloração para grafos cordais.
	///
	/// Complexidade: O(nlog(n) + m)
	vector<int> coloring() override;

	/// Calcula o número cromático do grafo.
	///
	/// Complexidade: O(nlog(n) + m)
	int chromaticNumber();

	/// Calcula o tamanho da maior clique do grafo.
	///
	/// Complexidade: O(nlog(n) + m)
	int maxClique();
};

///
/// Classe de exceções de construção de grafos cordais.
class ChordalConstructorException : public GraphException {
  public:
	///
	/// Construtor da exceção.
	ChordalConstructorException() {}

	///
	/// Retorna a mensagem de erro da exceção.
	const char *what() const throw() {
		return "constructor parameter is not chordal";
	}
};

#endif
