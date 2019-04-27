#ifndef GRAPH_DISPLAYH
#define GRAPH_DISPLAYH

#include "../vector/Vector.hpp"
#include "../graph/Graph.hpp"

#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

struct GraphDisplay {
	Graph G;
	bool temDir, temPeso, centr, draw;
	int raio, X, Y;
	vector<int> para;
	vector<Vector> pos;
	vector<Vector> vel;
	vector<float> posPeso;
	vector<string> peso;
	vector<int> color;
	vector<bool> isParal;

	GraphDisplay() {}
	GraphDisplay(Graph, int, int, int);
	void setGraph(Graph&);
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
	int achaVertice(Vector at);
	void centraliza();
	void addVertex(Vector);
	void removeVertex(int);
	void addEdge(int, int);
	void removeEdge(int);
	void itera();
};

#endif
