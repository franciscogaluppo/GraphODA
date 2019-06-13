#ifndef REPLH
#define REPLH

#include "Bipartite.hpp"
#include "Chordal.hpp"
#include "Dag.hpp"
#include "Graph.hpp"
#include "GraphCanvas.hpp"
#include "Interface.hpp"
#include "Tree.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

///
/// @file

namespace repl {
void run(int, int);
}

///
/// Classe para exceções do REPL.
class REPLException : public exception {
  public:
	///
	/// Construtor de exceções do REPL.
	REPLException() {}
	///
	/// Retorna mensagem de erro da exceção.
	/// @return Mensagem de erro;.
	const char *what() const throw() { return "REPL Exception"; }
};

///
/// Classe de exceções de comando inválido.
class REPLInvalidCommandException : public REPLException {
  public:
	///
	/// Construtor de exceções de comando inválido.
	REPLInvalidCommandException() {}
	///
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() { return "invalid syntax"; }
};

///
/// Classe de exceções de vértice não encontrado.
class REPLVertexNotFoundException : public REPLException {
  public:
	///
	/// Construtor de exceções de vértice não encontrado.
	/// @param string v que é o label de um vértice.
	REPLVertexNotFoundException(string v) {
		msg = "coudn't find vertex with label: " + v;
	}
	///
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() { return msg.c_str(); }

  private:
	string msg;
};

#endif
