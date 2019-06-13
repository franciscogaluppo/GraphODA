#ifndef BIPARTITEH
#define BIPARTITEH

#include "GraphGen.hpp"

///
/// @file

///
/// Classe para grafos bipartidos.
class Bipartite : public GraphGen {
  public:
	///
	/// Construtor para o grafo bipartido vazio
	Bipartite();

	///
	/// Construtor para o grafo bipartido por número de vértices.
	/// @param Número de vértices.
	Bipartite(int);

	///
	/// Construtor para o grafo bipartido por GraphGen.
	/// @param Grafo a ser convertido em Bipartite.
	Bipartite(GraphGen &);
};

///
/// Classe de exceções de construção de grafos bipartidos
class BipartiteConstructorException : public GraphException {
  public:
	///
	/// Construtor da exceção.
	BipartiteConstructorException() {}

	///
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() {
		return "constructor paramer is not bipartite";
	}
};

#endif
