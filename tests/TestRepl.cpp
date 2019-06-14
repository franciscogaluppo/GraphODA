#include "Repl.hpp"
#include "doctest.h"

void coloca() {
	Graph G = lerGrafoArquivo("./grafos/grafo1.txt");
	repl::vars["g"] = 0;
	repl::var = "g";
	repl::TYPE new_;
	new_.G = G;
	new_.type = 0;
	repl::at = 0;
	repl::graphs.push_back(new_);
}

void coloca2() {
	Graph G = lerGrafoArquivo("./grafos/grafo5.txt");
	repl::vars["g"] = 0;
	repl::var = "g";
	repl::TYPE new_;
	new_.G = G;
	new_.type = 0;
	repl::at = 0;
	repl::graphs.push_back(new_);
}

void limpa() {
	repl::graphs.clear();
	repl::vars.clear();
	repl::var = "";
	repl::at = 0, repl::lastVar = -1;
}

TEST_CASE("Teste REPL - getType") {
	limpa();
	CHECK(repl::getType(4) == "Tree");
}

TEST_CASE("Teste Dag - getGraphVar") {
	limpa();
	coloca();
	Graph G = repl::getGraphVar("g");
	CHECK(G.getN() == 5);
}

TEST_CASE("Teste REPL - getGraph") {
	limpa();
	coloca();
	Graph G = repl::getGraph();
	CHECK(G.getN() == 5);
}

TEST_CASE("Teste REPL - getVertex") {
	limpa();
	vector<string> v = {"aa", "bb", "cc", "dd"};
	Graph G(4, v);
	CHECK(repl::getVertex(G, "cc") == 2);
}

TEST_CASE("Teste REPL - undoDeclaration") {
	limpa();
	coloca();
	repl::undoDeclaration();
	CHECK(repl::vars.size() == 0);
}

TEST_CASE("Teste REPL - Error #1") {
	CHECK_NOTHROW(repl::fileNotFoundError("oi"));
}

TEST_CASE("Teste REPL - Error #2") {
	CHECK_NOTHROW(repl::undefinedVariableError("oi"));
}

TEST_CASE("Teste REPL - Error #3") {
	CHECK_NOTHROW(repl::wrongTypeError("g", 1));
}

TEST_CASE("Teste REPL - Error #4") {
	CHECK_NOTHROW(repl::graphIsNotError("oi", 1));
}

TEST_CASE("Teste REPL - Error #5") {
	CHECK_NOTHROW(repl::vertexNotFoundError("oi"));
}

TEST_CASE("Teste REPL - Error #6") {
	CHECK_NOTHROW(repl::noPathError("oi", "ola"));
}

TEST_CASE("Teste REPL - Error #7") {
	CHECK_NOTHROW(repl::negativeCycleError());
}

TEST_CASE("Teste REPL - import") {
	limpa();
	coloca();
	string l = "./grafos/grafo2.txt";
	repl::ss = stringstream(l);
	repl::import();
	CHECK(repl::graphs[0].G.getN() == 12);
}

TEST_CASE("Teste REPL - mst") {
	limpa();
	coloca();
	string l = "g";
	repl::ss = stringstream(l);
	repl::mst();
	CHECK(repl::graphs[0].T.getN() == 5);
}

TEST_CASE("Teste REPL - graphCast") {
	limpa();
	coloca2();
	string l = "g";
	repl::ss = stringstream(l);
	repl::graphCast();
	CHECK(repl::graphs[0].G.getN() == 12);
}

TEST_CASE("Teste REPL - bipartiteCast") {
	limpa();
	coloca2();
	string l = "g";
	repl::ss = stringstream(l);
	repl::bipartiteCast();
	CHECK(repl::graphs[0].B.getN() == 12);
}

TEST_CASE("Teste REPL - chordalCast") {
	limpa();
	coloca2();
	string l = "g";
	repl::ss = stringstream(l);
	repl::chordalCast();
	CHECK(repl::graphs[0].C.getN() == 12);
}

TEST_CASE("Teste REPL - dagCast") {
	limpa();
	coloca2();
	string l = "g";
	repl::ss = stringstream(l);
	repl::dagCast();
	CHECK(repl::graphs[0].D.getN() == 12);
}

TEST_CASE("Teste REPL - treeCast") {
	limpa();
	coloca2();
	string l = "g";
	repl::ss = stringstream(l);
	repl::treeCast();
	CHECK(repl::graphs[0].T.getN() == 12);
}

TEST_CASE("Teste REPL - describe") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::describe());
}

TEST_CASE("Teste REPL - reaches") {
	limpa();
	coloca();
	string l = "1 3";
	repl::ss = stringstream(l);
	CHECK_NOTHROW(repl::reaches());
}

TEST_CASE("Teste REPL - scc") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::scc());
}

TEST_CASE("Teste REPL - shortestPath") {
	limpa();
	coloca();
	string l = "1 3";
	repl::ss = stringstream(l);
	CHECK_NOTHROW(repl::shortestPath());
}

TEST_CASE("Teste REPL - coloring") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::coloring());
}

TEST_CASE("Teste REPL - chromaticNumber") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::chromaticNumber());
}

TEST_CASE("Teste REPL - greedyColoring") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::greedyColoring());
}

TEST_CASE("Teste REPL - maxClique") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::maxClique());
}

TEST_CASE("Teste REPL - artPoints") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::artPoints());
}

TEST_CASE("Teste REPL - bridges") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::bridges());
}

TEST_CASE("Teste REPL - topoSort") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::topoSort());
}

TEST_CASE("Teste REPL - center") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::center());
}

TEST_CASE("Teste REPL - diameter") {
	limpa();
	coloca();
	CHECK_NOTHROW(repl::diameter());
}
