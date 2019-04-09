#ifndef DRAW_GRAPHH
#define DRAW_GRAPHH

#include "../vector/Vector.hpp"
#include "../graph/Graph.hpp"

#include <bits/stdc++.h>
using namespace std;

void fdpPeso(Graph&, vector<Vector>&, vector<float>&, int);

Vector deixaDentro(Vector, int, int, float);

void fdp1(Graph&, vector<Vector>&, int, int, int, int, float);

vector<Vector> getPoligono(Graph&, int, int);

vector<Vector> getRandom(Graph&, int, int);

vector<Vector> getGood(Graph&, int, int, int, int);

#endif
