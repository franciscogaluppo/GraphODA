#include "doctest.h"
#include "Chordal.hpp"
#include "GraphCanvas.hpp"

/*
TEST_CASE()
{
	CHECK();
}

TEST_CASE()
{
	CHECK_THROWS_AS(, );
}
*/

TEST_CASE("Teste Cordal - Número cromático #1")
{
	// grafo 1
	Chordal G = lerGrafoArquivo("../grafos/grafo1.txt");
	CHECK(G.chromaticNumber() == 3);
}

TEST_CASE("Teste Cordal - Número cromático #2")
{
	// grafo 3
	Chordal G = lerGrafoArquivo("../grafos/grafo3.txt");
	CHECK(G.chromaticNumber() == 5);
}

TEST_CASE("Teste Cordal - Número cromático #3")
{
	// grafo 5
	Chordal G = lerGrafoArquivo("../grafos/grafo5.txt");
	CHECK(G.chromaticNumber() == 2);
}

TEST_CASE("Teste Cordal - Número cromático #4")
{
	// grafo 7
	Chordal G = lerGrafoArquivo("../grafos/grafo7.txt");
	CHECK(G.chromaticNumber() == 2);
}

TEST_CASE("Teste Cordal - Número cromático #5")
{
	// grafo 10
	Chordal G = lerGrafoArquivo("../grafos/grafo10");
	CHECK(chromaticNumber() == 3);
}

TEST_CASE("Teste Cordal - Número cromático #6")
{
	// grafo 12
	Chordal G = lerGrafoArquivo("../grafos/grafo12.txt");
	CHECK(G.chromaticNumber() == 2);
}

TEST_CASE("Teste Cordal - Número cromático #7")
{
	// grafo 14
	Chordal G = lerGrafoArquivo("../grafos/grafo14.txt");
	CHECK(G.chromaticNumber() == 5);
}

TEST_CASE("Teste Cordal - Construtor #1")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo2.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #2")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo4.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #3")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo6.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #4")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo8.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #5")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo9.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #6")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo11.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #7")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo13.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}

TEST_CASE("Teste Cordal - Construtor #8")
{
	GraphGen G = lerGrafoArquivo("../grafos/grafo15.txt");
	CHECK_THROWS_AS(Chordal(G), ChordalConstructorException);
}
