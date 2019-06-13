#ifndef TREEH
#define TREEH

#include "Chordal.hpp"

///
/// @file

///
/// Classe para árvores.
class Tree : public Chordal {
  public:
	///
	/// Construtor de árvores vazias.
	Tree();

	///
	/// Construtor de árvores por número de vértices.
	/// @param Número de vértices.
	Tree(int);

	///
	/// Construtor de árvores por GraphGen.
	/// @param Grafo a ser convertido em Tree.
	Tree(GraphGen &);

	///
	/// Computa centro da árvore.
	/// @return Vértice centro da árvore.
	int center();

	///
	/// Computa diâmetro da árvore.
	/// @return Diâmetro da árvore.
	int diameter();

	///
	/// Computa centroid da árvore.
	/// @return Centroid da árvore.
	int centroid();

  private:
	pair<int, vector<int> > bfsCenter(int);
};

///
/// Classe de exceções de construção de árvores.
class TreeConstructorException : public GraphException {
  public:
	///
	/// Construtor da exceção.
	TreeConstructorException() {}

	///
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() {
		return "constructor parameter is not a tree";
	}
};

#endif
