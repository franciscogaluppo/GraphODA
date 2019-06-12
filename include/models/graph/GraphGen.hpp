#ifndef GRAPHGENH
#define GRAPHGENH

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/// @file
///
/// Classe para grafos gerais.
class GraphGen {
  public:
	///
	/// Lista de rótulos dos vértices.
	vector<string> label;

	///
	/// Construtor para o grafo vazio.
	GraphGen();

	///
	/// Construtor para o grafo por número de vértices.
	GraphGen(int);

	///
	/// Construtor para o grafo por número de vértices e seus rótulos.
	GraphGen(int, vector<string> &);

	// gets
	///
	/// Retorna o número de vértices
	int getN();

	///
	/// Retorn o número de arestas.
	int getM();

	///
	/// Retorna a lista de adjacência direcionada.
	vector<vector<pair<int, int>>> getAdj();

	///
	/// Retorn a lista de adjacência não direcionada.
	vector<vector<pair<int, int>>> getSimAdj();

	///
	/// Retorna a lista das arestas.
	vector<pair<int, int>> getEdges();

	///
	/// Retorna a lista de pesos das arestas.
	vector<int> getPesos();

	///
	/// Retorna .
	vector<vector<int>> getMatrix();

	///
	/// Retorna .
	vector<vector<int>> getSimMatrix();

	// auxiliares
	///
	/// Retorna se o grafo possui arestas com pesos.
	bool isWeighted();

	///
	/// Retorna se o grafo possui arestas com pesos negativos.
	bool hasNegativeWeight();

	///
	/// Retorna se dois vértices se alcançam.
	bool reaches(int, int);

	///
	/// Retorna se o grafo é conexo
	bool isConnected();

	// reconhecedores
	///
	/// Retorna se o grafo é bipartido.
	bool isBipartite();

	///
	/// Retorna se o grafo é cordal.
	bool isChordal();

	///
	/// Retorna se o grafo é direcionado acíclico.
	bool isDag();

	///
	/// Retorna se o grafo é uma árvore.
	bool isTree();

	// algoritmos
	/// Retorna uma lista com a componente fortemente conexa de cada vértices.
	///
	/// Complexidade: O(n + m)
	vector<int> scc();

	// TODO
	/// Retorna o menor caminho entre dois vértices.
	///
	/// Complexidade: O()
	long long shortestPath(int, int);

	// TODO
	/// Retorna uma lista com a cor de cada vértice em uma coloração mínima.
	///
	/// Complexidade: O()
	virtual vector<int> coloring();

	/// Retorna uma lista com a cor de cada vértice em uma coloração gulosa na
	/// ordem dos vértices.
	///
	/// Complexidade: O(n + m)
	vector<int> greedyColoring();

	/// Retorna uma lista com a cor de cada vértice em uma coloração gulosa para
	/// uma dada ordem dos vértices.
	///
	/// Complexidade: O(n + m)
	vector<int> greedyColoring(vector<int>);

	/// Retorna um vetor de booleanos que informa se cada vértice é um ponto de
	/// articulação
	///
	/// Complexidade: O(n + m)
	vector<bool> artPoints();

	/// Retorna um vetor de booleanos que informa se cada aresta é uma ponte
	///
	/// Complexidade: O(n + m)
	vector<pair<int, int>> bridges();

  protected:
	///
	/// Número de vértices do grafo.
	int n;

	///
	/// Número de arestas do grafo.
	int m;

	///
	/// Lista de adjacência direcionada.
	vector<vector<pair<int, int>>> adj;

	///
	/// Lista de adjacência não direcionada.
	vector<vector<pair<int, int>>> simAdj;

	/// Retorna uma ordenação dos vértices, e sua ordenação inversa, de máxima
	/// caridinalidade (uma ordenação simplicial se e somente se o grafo for
	/// cordal).
	///
	/// Complexidade: O(nlog(n) + m)
	pair<vector<int>, vector<int>> maximumCardinalitySearch();

	/// Verifica se uma ordenação dos vértices (e sua ordenação inversa) possui
	/// as propriedades de de Zero-Fill-In (i.e., se o grafo é cordal).
	///
	/// Complexidade: O(n + m)
	bool zeroFillIn(pair<vector<int>, vector<int>>);

	/// Verifica se uma ordenação atende às exigências de uma ordenação.
	bool checkOrdering(vector<int>);

  private:
	// auxiliares
	// TODO
	/// .
	///
	/// Complexidade: O()
	bool dfsReaches(vector<bool> &, int, int);

	// TODO
	/// .
	///
	/// Complexidade: O()
	void dfsCheckConnected(vector<bool> &, int);

	// TODO
	/// .
	///
	/// Complexidade: O()
	bool dfsCheckBipartite(int, int, vector<int> &);

	// TODO
	/// .
	///
	/// Complexidade: O()
	bool dfsCheckDag(int, vector<int> &);

	// TODO
	/// .
	///
	/// Complexidade: O()
	bool dfsCheckTree(int, int, vector<int> &);

	// TODO
	/// .
	///
	/// Complexidade: O()
	int dfsScc(vector<int> &, vector<int> &, vector<int> &, int &, int &, int);

	// TODO
	/// .
	///
	/// Complexidade: O()
	void dfsArt(vector<bool> &, vector<int> &, vector<int> &, vector<int> &,
				vector<bool> &, vector<pair<int, int>> &, int, int, int &);

	// algoritmos
	// TODO
	/// .
	///
	/// Complexidade: O()
	long long shortestPathBFS(int, int);

	// TODO
	/// .
	///
	/// Complexidade: O()
	long long dijkstra(int, int);

	// TODO
	/// .
	///
	/// Complexidade: O()
	long long bellmanFord(int, int);
};

///
/// Classe de exceções de grafos.
class GraphException : public exception {
  public:
	GraphException() {}

	///
	/// Retorna a mensagem de erro da exceção.
	const char *what() const throw() { return "Graph Exception"; }
};

///
/// Classe de exceções de ausência de caminho entre dois vértices.
class GraphNoPathException : public GraphException {
  public:
	/// Construtor para a exceção de
	/// ausência de caminho entre dois vértices
	GraphNoPathException(int a, int b) {
		msg = "no path from " + to_string(a) + " to " + to_string(b);
	}

	///
	/// Retorna a mensagem de erro da exceção.
	const char *what() const throw() { return msg.c_str(); }

  private:
	string msg;
};

///
/// Classe de exceções para ciclos negativos em caminhos mínimos.
class GraphNegativeCycleException : public GraphException {
  public:
	GraphNegativeCycleException() {}

	///
	/// Retorna a mensagem de erro da exceção.
	const char *what() const throw() {
		return "negative cycle found; shortest path is undefined";
	}
};

///
/// Classe de exceções para ordenações de vértices fora do domínio.
class GraphOrderingException : public GraphException {
  public:
	GraphOrderingException() {}

	///
	/// Retorna a mensagem de erro da exceção.
	const char *what() const throw() { return "not a valid vertex ordering"; }
};

#endif
