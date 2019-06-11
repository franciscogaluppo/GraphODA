#ifndef DAGH
#define DAGH

#include "GraphGen.hpp"

///
/// @file

///
/// Classe para grafos direcionados acíclicos.
class Dag : public GraphGen {
  public:

		///
		/// Construtor de DAGs vazios.
		Dag();

		///
		/// Construtor de DAGs por número de vértices.
		Dag(int);

		///
		/// Construtor de DAGs por por GraphGen.
		Dag(GraphGen &);
};

///
/// Classe de exceção de construção de DAGs.
class DagConstructorException : public GraphException {
  public:
		///
		/// Construtor da exceção.
		DagConstructorException() {}

		///
		/// Retorna a mensagem de erro da exceção.
		const char *what() const throw() {
			return "construcor parameter is not a dag";
	}
};

#endif
