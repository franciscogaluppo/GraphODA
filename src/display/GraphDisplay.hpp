#ifndef GRAPH_DISPLAYH
#define GRAPH_DISPLAYH

#include "../vector/Vector.hpp"
#include "../graph/Graph.hpp"

#include <bits/stdc++.h>
using namespace std;

struct GraphDisplay {
	Graph G;
	bool temDir, temPeso;
	int raio, X, Y, clique;
	vector<Vector> pos;
	vector<float> posPeso;
	vector<string> peso;
	vector<int> color;

	GraphDisplay(Graph, int, int, int);
	void fdpPeso(int);
	Vector deixaDentro(Vector);
	void fdp1(int);
	void fdp2(int);
	int inter();
	void poligono();
	void random();
	void good(int, int);
};

#endif
