#include "Chordal.hpp"
#include "Graph.hpp"
#include "GraphCanvas.hpp"
#include "doctest.h"

TEST_CASE("Teste Cordal - Número cromático #1") {
	Graph g = lerGrafoArquivo("../grafos/grafo1.txt");
	Chordal G(g);
	CHECK(G.chromaticNumber() == 3);
}

TEST_CASE("Teste Cordal - Número cromático #2") {
	Graph g = lerGrafoArquivo("../grafos/grafo3.txt");
	Chordal G(g);
	CHECK(G.chromaticNumber() == 5);
}

TEST_CASE("Teste Cordal - Número cromático #3") {
	Graph g = lerGrafoArquivo("../grafos/grafo5.txt");
	Chordal G(g);
	CHECK(G.chromaticNumber() == 2);
}

TEST_CASE("Teste Cordal - Número cromático #4") {
	Graph g = lerGrafoArquivo("../grafos/grafo7.txt");
	Chordal G(g);
	CHECK(G.chromaticNumber() == 2);
}

TEST_CASE("Teste Cordal - Número cromático #5") {
	Graph g = lerGrafoArquivo("../grafos/grafo10");
	Chordal G(g);
	CHECK(G.chromaticNumber() == 3);
}

TEST_CASE("Teste Cordal - Número cromático #6") {
	Graph g = lerGrafoArquivo("../grafos/grafo12.txt");
	Chordal G(g);
	CHECK(G.chromaticNumber() == 2);
}

TEST_CASE("Teste Cordal - Número cromático #7") {
	Graph g = lerGrafoArquivo("../grafos/grafo14.txt");
	Chordal G(g);
	CHECK(G.chromaticNumber() == 5);
}

TEST_CASE("Teste Cordal - Construtor #1") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo2.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #2") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo4.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #3") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo6.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #4") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo8.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #5") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo9.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #6") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo11.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #7") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo13.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #8") {
	GraphGen G = lerGrafoArquivo("../grafos/grafo15.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}