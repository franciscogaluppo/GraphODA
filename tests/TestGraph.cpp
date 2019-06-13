#include "Graph.hpp"
#include "GraphGen.hpp"
#include "GraphCanvas.hpp"
#include "doctest.h"

TEST_CASE("Teste Graph - MST #1") {
	Graph G = lerGrafoArquivo("../grafos/grafo1.txt");
	CHECK(G.mst().isTree());
}

TEST_CASE("Teste Graph - MST #2") {
	Graph G = lerGrafoArquivo("../grafos/grafo1.txt");
	GraphGen H(G);
	Graph I(H);
	CHECK(I.mst().isTree());
}

TEST_CASE("Teste Graph - Add Edge #1") {
	Graph G(5);
	G.addEdge(0, 1);
	CHECK(G.getM() == 1);
}

TEST_CASE("Teste Graph - MST Edges")
{
	Graph G(2);
	G.addEdge(0, 1);
	CHECK(G.mstEdges().size() == 1);
}


