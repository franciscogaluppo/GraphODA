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
	Graph(int);

	///
	/// Construtor do grafo por número de vértices e seus rótulos.
	Graph(int, vector<string> &);

	///
	/// Construtor do grafo por GraphGen.
	Graph(GraphGen &);

	///
	/// Adiciona aresta sem peso entre dois vértices.
	void addEdge(int, int);

	///
	/// Adiciona aresta com peso entre dois vértices.
	void addEdge(int, int, int);

	/// Encontra uma árvore geradora mínima para o grafo.
	///
	/// Complexidade: O()
	Tree mst();

	/// Retorna uma lista das arestas que pertencem a uma árvore
	/// geradora mínima.
	///
	/// Complexidade: O()
	vector<bool> mstEdges();
};

///
/// Classe de exceções de vértice fora dos limites.
class GraphVertexOutOfBoundsException : public GraphException {
  public:
	///
	/// Construtor da exceção.
	GraphVertexOutOfBoundsException(int n) {
		msg = "vertex out of bounds: " + to_string(n);
	}

	///
	/// Retorna a mensagem de erro da exceção.
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
	GraphSelfLoopException(int n) {
		msg = "self loop not allowed (at vertex " + to_string(n) + ")";
	}

	///
	/// Retorna a mensagem de erro da exceção.
	const char *what() const throw() { return msg.c_str(); }

  private:
	///
	/// Mensagem de erro da exceção.
	string msg;
};

#endif
