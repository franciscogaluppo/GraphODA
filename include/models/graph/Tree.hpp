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
	Tree(int);

	///
	/// Construtor de árvores por GraphGen.
	Tree(GraphGen &);
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
	const char *what() const throw() {
		return "constructor parameter is not a tree";
	}
};

#endif
