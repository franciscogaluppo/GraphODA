#ifndef GRAPHGENH
#define GRAPHGENH

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <string>
#include <queue>
#include <utility>
#include <numeric>

using namespace std;

/// @file
///
/// Classe para grafos gerais.
class GraphGen {
	public:
		vector<string> label;

		GraphGen();
		GraphGen(int);
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

		/// Retorna o menor caminho entre dois vértices.
		///
		/// Complexidade: O()
		long long shortestPath(int, int);

		/// Retorna uma lista com a cor de cada vértice em uma coloração mínima.
		///
		/// Complexidade: O()
		virtual vector<int> coloring();

		/// Retorna uma lista com a cor de cada vértice em uma coloração gulosa na ordem dos vértices.
		/// Complexidade: O(n + m)
		vector<int> greedyColoring();

		/// Retorna uma lista com a cor de cada vértice em uma coloração gulosa para uma dada ordem dos vértices.
		///
		/// Complexidade: O(n + m)
		vector<int> greedyColoring(vector<int>);

	protected:
		int n, m;
		vector<vector<pair<int, int>>> adj;
		vector<vector<pair<int, int>>> simAdj;

		/// Retorna uma ordenação dos vértices, e sua ordenação inversa, de máxima caridinalidade (uma ordenação simplicial se e somente se o grafo for cordal).
		///
		/// Complexidade: O(nlog(n) + m)
		pair<vector<int>, vector<int>> maximumCardinalitySearch();

		/// Verifica se uma ordenação dos vértices (e sua ordenação inversa) possui as propriedades de de Zero-Fill-In (i.e., se o grafo é cordal).
		///
		/// Complexidade: O(n + m)
		bool zeroFillIn(pair<vector<int>, vector<int>>);

		/// Verifica se uma ordenação atende às exigências de uma ordenação.
		bool checkOrdering(vector<int>);

	private:
		// auxiliares
		bool dfsReaches(vector<bool>&, int, int);
		bool dfsCheckBipartite(int, int, vector<int>&);
		bool dfsCheckDag(int, vector<int>&);
		bool dfsCheckTree(int, int, vector<int>&);
		int dfsScc(vector<int>&, vector<int>&, vector<int>&, int&, int&, int);
		
		// algoritmos
		long long shortestPathBFS(int, int);
		long long dijkstra(int, int);
		long long bellmanFord(int, int);
};

class GraphException : public exception {
	public:
		GraphException() {}
		const char *what() const throw () { return "Graph Exception"; }
};

class GraphNoPathException : public GraphException {
	public:
		GraphNoPathException(int a, int b) {
			msg = "no path from "+to_string(a)+" to "+to_string(b);	
		}
		const char *what() const throw () { return msg.c_str(); }

	private:
		string msg;
};

class GraphNegativeCycleException : public GraphException {
	public:
		GraphNegativeCycleException() {}
		const char *what() const throw () { return "negative cycle found; shortest path is undefined"; }
};

class GraphOrderingException: public GraphException
{
	public:
		GraphOrderingException() {}
		const char *what() const throw ()
		{
			return "not a valid vertex ordering";
		}
};

#endif
