#include "Repl.hpp"
#include "doctest.h"

void coloca() {
	Graph G = lerGrafoArquivo("../grafos/grafo1.txt");
	repl::vars["g"] = 0;
	repl::var = "g";
	repl::TYPE new_;
	new_.G = G;
	new_.type = 0;
	repl::at = 0;
	repl::graphs.push_back(new_);
}

void coloca2() {
	Graph G = lerGrafoArquivo("../grafos/grafo5.txt");
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

TEST_CASE("Teste REPL - import") {
	limpa();
	coloca();
	string l = "../grafos/grafo2.txt";
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

TEST_CASE("Teste REPL - reaches") {
	limpa();
	coloca();
	string l = "a";
	repl::ss = stringstream(l);
	CHECK_THROWS_AS(repl::reaches(), REPLInvalidCommandException);
}

TEST_CASE("Teste REPL - shortestPath") {
	limpa();
	coloca();
	string l = "a";
	repl::ss = stringstream(l);
	CHECK_THROWS_AS(repl::shortestPath(), REPLInvalidCommandException);
}
