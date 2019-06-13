#ifndef GRAPH_DISPLAYH
#define GRAPH_DISPLAYH

#include "Graph.hpp"
#include "Vector.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

///
/// @file

///
/// Classe para display do grafo.
class GraphDisplay {
	public:
		///
		/// Grafo que está sendo representado.
		Graph G;

		///
		/// Variável que indica se o grafo deve ser representado de forma
		/// direcionada.
		bool temDir;

		///
		/// Variável que indica se está no modo 'centralizar'.
		bool centr;

		///
		/// Variável que indica se o display está no modo 'draw'.
		bool draw;

		///
		/// Tamanho do raio da representação de cada vértice.
		int raio;

		///
		/// Tamanho do eixo horizontal do canvas.
		int X;

		///
		/// Tamanho do eixo vertical do canvas.
		int Y;

		///
		/// Lista que indica se cada vértice deve ser parado (quando o usuário
		/// clica nele).
		vector<bool> para;

		///
		/// Lista que indica se cada vértice está travado.
		vector<bool> trava;

		///
		/// Lista contendo a posição de cada vértice.
		vector<Vector> pos;

		///
		/// Lista contendo a velocidade de cada vértice.
		vector<Vector> vel;

		///
		/// Lista contendo a posição de cada peso em relação à sua aresta.
		///
		/// Valores vão de 0 a 1, de forma que 0.5 indica que o peso está
		/// no meio da aresta.
		vector<float> posPeso;

		///
		/// Lista contendo a cor de cada vértice.
		vector<int> color;

		///
		/// Lista contendo a cor de cada aresta.
		vector<int> colorAresta;

		///
		/// Lista que indica se cada aresta é 'paralela' ou não.
		vector<bool> isParal;

		///
		/// Construtor de GraphDisplay vazio.
		GraphDisplay() {}

		///
		/// Construtor de GraphDisplay com base no seu grafo, nas dimensões do
		/// canvas e no tamanho do raio do vértice.
		GraphDisplay(Graph, int, int, int);

		///
		/// Seta um grafo no display.
		void setGraph(Graph &);

		///
		/// Seta um grafo no display, mantendo as confugurações do grafo anterior.
		void setGraphContinue(Graph &);

		///
		/// Algoritmo de display para os pesos.
		void fdpPeso(int);

		///
		/// Garante que um vértice está dentro do canvas.
		Vector deixaDentro(Vector, bool);

		///
		/// Verifica se uma posição está dentrod do canvas.
		bool taDentro(Vector);

		///
		/// ALgoritmo de display de Eades.
		void fdpEades(int);

		///
		/// Algoritmo de display de Eades usando aceleração.
		void fdpEadesAcc(int);

		///
		/// Algoritmo de display de Fruchterman.
		void fdpFruchterman(int);

		///
		/// Computa número de interseções de arestas no display atual.
		int inter();

		///
		/// Algoritmo display polígono.
		void poligono();

		///
		/// Display aleatório
		void random();

		///
		/// Tenta encontrar um display visualmente agradável.
		void good(int, int);

		///
		/// Encontra vértice em dada posição.
		int achaVertice(Vector);

		///
		/// Encontra aresta em dada posição.
		int achaAresta(Vector);

		///
		/// Reseta as cores dos vértices e arestas.
		void resetColors();

		///
		/// Adiciona um vértice em dada posição.
		void addVertex(Vector);

		///
		/// Remove um dado vértice.
		void removeVertex(int);

		///
		/// Adiciona uma aresta entre dois vértices.
		void addEdge(int, int);

		///
		/// Reomove uma dada aresta.
		void removeEdge(int);

		///
		/// Itera a animação do display.
		void itera();
};

#endif
