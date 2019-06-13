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
	/// @param Número de vértices.
	Dag(int);

	///
	/// Construtor de DAGs por por GraphGen.
	/// @param Grafo a ser convertido em DAG.
	Dag(GraphGen &);

	///
	/// Computa ordenação topológica.
	/// @return Ordenação topológica dos vértices.
	vector<int> topoSort();

  private:
	void topoSortDfs(vector<bool> &, vector<int> &, int);
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
	/// @return Mensagem de erro.
	const char *what() const throw() {
		return "construcor parameter is not a dag";
	}
};

#endif
