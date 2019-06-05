#include "Chordal.hpp"

Chordal::Chordal() : GraphGen() {}

Chordal::Chordal(int n) : GraphGen(n) {}

Chordal::Chordal(GraphGen& G) {
	if (!G.isChordal()) throw ChordalConstructorException();

	n = G.getN();
	m = G.getM();
	label = G.label;
	adj = G.getAdj();
	simAdj = G.getSimAdj();
}

vector<int> Chordal::perfectEliminationOrdering()
{
	return maximumCardinalitySearch().second;
}

vector<int> Chordal::coloring()
{
	vector<int> alpha = perfectEliminationOrdering();
	vector<int> colors (n, 0);
	vector<int> vizinhanca;
	vector<bool> visitado (n, false);

	// Itera pela ordenação de trás para frente
	for(int i = n-1; i >= 0; i--)
	{
		int max = 0;
		vizinhanca.clear();
		fill(visitado.begin(), visitado.end(), false);

		// Vê quais cores dos vizinhos
		for(auto u: simAdj[alpha[i]])
		{
			int w = u.first;
			if(visitado[w])
				continue;

			visitado[w] = true;
			if(colors[w])
				vizinhanca.push_back(colors[w]);
			max++;
		}
		
		// Marca as cores usadas
		vector<int> possiveis (max+1, 0);
		for(auto c: vizinhanca)
			if(c <= max)
			   possiveis[c-1]++;	
		
		// Seleciona a menor cor não usada
		for(int j = 0; j <= max; j++)
			if(possiveis[j] == 0)
			{
				colors[alpha[i]] = j+1;
				break;
			}

		if(!max)
			colors[alpha[i]] = 1;
	}

	return colors;
}

int Chordal::chromaticNumber()
{
	vector<int> cores = coloring();
	int maior = 0;
	for(auto c: cores)
		maior = (c > maior? c: maior);
	return maior;
}
