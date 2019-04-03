#ifndef DRAW_GRAPHH
#define DRAW_GRAPHH

#include "../vector/Vector.hpp"
#include "../graph/Graph.hpp"

#include <bits/stdc++.h>
using namespace std;

Vector deixaDentro(Vector, int, int, float);

void fdp1(Graph&, vector<Vector>&, int, int, int, int, float);

vector<Vector> getPoligono(Graph&, int, int);

#endif
