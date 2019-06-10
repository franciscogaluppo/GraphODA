#ifndef GRAPH_DISPLAYH
#define GRAPH_DISPLAYH

#include "Graph.hpp"
#include "Vector.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

struct GraphDisplay {
	Graph G;
	bool temDir, centr, draw;
	int raio, X, Y;
	vector<bool> para, trava;
	vector<Vector> pos;
	vector<Vector> vel;
	vector<float> posPeso;
	vector<int> color;
	vector<int> colorAresta;
	vector<bool> isParal;

	GraphDisplay() {}
	GraphDisplay(Graph, int, int, int);
	void setGraph(Graph &);
	void setGraphContinue(Graph &);
	void fdpPeso(int);
	Vector deixaDentro(Vector, bool);
	bool taDentro(Vector);
	void fdpEades(int);
	void fdpEadesAcc(int);
	void fdpFruchterman(int);
	int inter();
	void poligono();
	void random();
	void good(int, int);
	int achaVertice(Vector);
	int achaAresta(Vector);
	void centraliza();
	void resetColors();
	void addVertex(Vector);
	void removeVertex(int);
	void addEdge(int, int);
	void removeEdge(int);
	void itera();
};

#endif
