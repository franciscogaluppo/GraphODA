#include "Graph.hpp"
#include "Dag.hpp"
#include "GraphCanvas.hpp"
#include "doctest.h"

TEST_CASE("Teste Dag - toposort") {
	Graph G = lerGrafoArquivo("../grafos/grafo5.txt");
	Dag H(G);
	CHECK(H.topoSort().size() == H.getN());
}

