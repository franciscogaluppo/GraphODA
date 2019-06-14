#include "Graph.hpp"
#include "Bipartite.hpp"
#include "GraphCanvas.hpp"
#include "doctest.h"

TEST_CASE("Teste Dag - bipartite") {
	Graph G = lerGrafoArquivo("./grafos/grafo5.txt");
	Bipartite H(G);
	CHECK(H.getN() == 12);
}

TEST_CASE("Teste Dag - bipartite") {
	Bipartite H(12);
	CHECK(H.getN() == 12);
}
