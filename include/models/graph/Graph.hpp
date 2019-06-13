#ifndef GRAPH
#define GRAPH

#include "Bipartite.hpp"
#include "Chordal.hpp"
#include "DSU.hpp"
#include "Dag.hpp"
#include "GraphGen.hpp"
#include "Tree.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

///
/// @file

///
/// Classe para grafos.
class Graph : public GraphGen {
  public:
	///
	/// Construtor do grafo.
	Graph();

	///
	/// Construtor do grafo por número de vértices
	/// @param Número de vértices.
	Graph(int);

	///
	/// Construtor do grafo por número de vértices e seus rótulos.
	/// @param Número de vértices.
	/// @param Lista de rótulos.
	Graph(int, vector<string> &);

	///
	/// Construtor do grafo por GraphGen.
	/// @param Grafo a ser convertido em Graph.
	Graph(GraphGen &);

	///
	/// Adiciona aresta sem peso entre dois vértices.
	/// @param Vértices que definem a aresta.
	void addEdge(int, int);

	///
	/// Adiciona aresta com peso entre dois vértices.
	/// @param Vértices que definem a aresta.
	/// @param peso da aresta.
	void addEdge(int, int, int);

	/// Encontra uma árvore geradora mínima para o grafo.
	///
	/// Complexidade: O(m log(m))
	/// @return Tree que representa a árvore geradora mínima do grafo.
	Tree mst();

	/// Retorna uma lista das arestas que pertencem a uma árvore
	/// geradora mínima.
	///
	/// Complexidade: O(m log(m))
	/// @return Vetor que indica se cada aresta pertence à árvore geradora
	/// mínima, ou não.
	vector<bool> mstEdges();
};

///
/// Classe de exceções de vértice fora dos limites.
class GraphVertexOutOfBoundsException : public GraphException {
  public:
	///
	/// Construtor da exceção.
	/// @param Vértice fora do limite.
	GraphVertexOutOfBoundsException(int n) {
		msg = "vertex out of bounds: " + to_string(n);
	}

	///
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() { return msg.c_str(); }

  private:
	///
	/// Mensagem de erro da exceção.
	string msg;
};

///
/// Classe de exceções de laços.
class GraphSelfLoopException : public GraphException {
  public:
	///
	/// Construtor da exceção.
	/// @param Vértice no qual o self-loop ocorreu.
	GraphSelfLoopException(int n) {
		msg = "self loop not allowed (at vertex " + to_string(n) + ")";
	}

	///
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() { return msg.c_str(); }

  private:
	///
	/// Mensagem de erro da exceção.
	string msg;
};

#endif
