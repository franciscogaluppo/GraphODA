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
	/// @param Número de vértices.
	Chordal(int);

	///
	/// Construtor de grafos cordais por GraphGen
	/// @param Grafo a ser convertido em Chordal.
	Chordal(GraphGen &);

	// Algoritmos
	/// Cria uma ordem de eliminação perfeita dos vértices.
	///
	/// Complexidade: O(nlog(n))
	/// @return Ordem de eliminação perfeita.
	vector<int> perfectEliminationOrdering();

	/// Algoritmo de coloração para grafos cordais.
	///
	/// Complexidade: O(nlog(n) + m)
	/// @return Lista das cores de cada vértice.
	vector<int> coloring() override;

	/// Calcula o número cromático do grafo.
	///
	/// Complexidade: O(nlog(n) + m)
	/// @return Número cromático do grafo.
	int chromaticNumber();

	/// Calcula o tamanho da maior clique do grafo.
	///
	/// Complexidade: O(nlog(n) + m)
	/// @return Tamanho da maior clique do grafo.
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
	/// @return Mensagem de erro.
	const char *what() const throw() {
		return "constructor parameter is not chordal";
	}
};

#endif
