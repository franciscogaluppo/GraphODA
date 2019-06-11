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
		Bipartite(int);

		///
		/// Construtor para o grafo bipartido por GraphGen.
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
		const char *what() const throw() {
			return "constructor paramer is not bipartite";
	}
};

#endif
