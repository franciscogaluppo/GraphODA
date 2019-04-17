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
	bool temDir, temPeso, centr;
	int raio, X, Y;
	vector<int> para;
	vector<Vector> pos;
	vector<Vector> vel;
	vector<float> posPeso;
	vector<string> peso;
	vector<int> color;

	GraphDisplay(Graph, int, int, int);
	void fdpPeso(int);
	Vector deixaDentro(Vector, bool);
	void fdpEades(int);
	void fdpEadesAcc(int);
	void fdpFruchterman(int);
	int inter();
	void poligono();
	void random();
	void good(int, int);
	int achaVertice(Vector at);
	void centraliza();
	void itera();
};

#endif
