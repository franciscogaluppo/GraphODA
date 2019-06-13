#include "Graph.hpp"
#include "GraphCanvas.hpp"
#include "doctest.h"

TEST_CASE("Teste GraphGen - GetMatrix #1") {
	Graph G = lerGrafoArquivo("../grafos/grafo1.txt");
	GraphGen H(G);

	CHECK(H.getMatrix().size() == H.getN());
}

TEST_CASE("Teste GraphGen - GetMatrix #2") {
	Graph G = lerGrafoArquivo("../grafos/grafo2.txt");
	GraphGen H(G);

	CHECK(H.getSimMatrix().size() == H.getN());
}

TEST_CASE("Teste GraphGen - isWeighted Edges")
{
	Graph G = lerGrafoArquivo("../grafos/grafo3.txt");
	GraphGen H(G);

	CHECK(!H.isWeighted());
}

TEST_CASE("Teste GraphGen - É conexo")
{
	Graph G = lerGrafoArquivo("../grafos/grafo4.txt");
	GraphGen H(G);

	CHECK(H.isConnected());
}

TEST_CASE("Teste GraphGen - Se é bipartido")
{
	Graph G = lerGrafoArquivo("../grafos/grafo5.txt");
	GraphGen H(G);

	CHECK(H.isBipartite());
}

TEST_CASE("Teste GraphGen - Se é DAG")
{
	Graph G = lerGrafoArquivo("../grafos/grafo6.txt");
	GraphGen H(G);

	CHECK(H.isDag());
}

TEST_CASE("Teste GraphGen - SCC")
{
	Graph G = lerGrafoArquivo("../grafos/grafo7.txt");
	GraphGen H(G);

	CHECK(H.scc().size() == H.getN());
}

TEST_CASE("Teste GraphGen - coloração")
{
	Graph G = lerGrafoArquivo("../grafos/grafo8.txt");
	GraphGen H(G);

	CHECK(H.greedyColoring().size() == H.getN());
}

TEST_CASE("Teste GraphGen - a reaches b")
{
	Graph G = lerGrafoArquivo("../grafos/grafo9.txt");
	GraphGen H(G);

	CHECK(H.reaches(0,1));
}

TEST_CASE("Teste GraphGen - caminho minimo")
{
	Graph G = lerGrafoArquivo("../grafos/grafo10.txt");
	G.addEdge(0, 1, -1);
	GraphGen H(G);

	CHECK(H.shortestPath(0,1));
}

TEST_CASE("Teste GraphGen - caminho minimo")
{
	Graph G = lerGrafoArquivo("../grafos/grafo15.txt");
	GraphGen H(G);

	CHECK(H.shortestPath(0,1));
}

TEST_CASE("Teste GraphGen - pontos de art")
{
	Graph G = lerGrafoArquivo("../grafos/grafo12.txt");
	GraphGen H(G);

	CHECK(H.artPoints().size() == H.getN());
}

TEST_CASE("Teste GraphGen - pontes")
{
	Graph G = lerGrafoArquivo("../grafos/grafo12.txt");
	GraphGen H(G);

	CHECK(H.bridges().size() == 2);
}
