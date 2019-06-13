#include "Tree.hpp"
#include "Graph.hpp"
#include "GraphCanvas.hpp"
#include "doctest.h"

TEST_CASE("Teste Tree - Centro #1") {
	Graph g = lerGrafoArquivo("../grafos/grafo7.txt");
	Tree G(g);
	CHECK(G.center() == 0);
}

TEST_CASE("Teste Tree - Diametro #1") {
	Graph g = lerGrafoArquivo("../grafos/grafo5.txt");
	Tree G(g);
	CHECK(G.diameter() == 33);
}

