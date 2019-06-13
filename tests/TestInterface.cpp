#include "Interface.hpp"
#include "doctest.h"

TEST_CASE("Teste Interface #1") {
	Graph G = lerGrafoArquivo("../grafos/grafo1.txt");
	//interface::display(1, 1);
	CHECK(true);
}
