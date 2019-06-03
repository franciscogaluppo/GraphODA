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
	vector<set<int> > Set (n);
	vector<int> size (n, 0);
	vector<int> alpha (n);
	vector<bool> visitado (n, 0);
	int i = n-1, j = 0;

	for(int i = 0; i < n; i++)
		Set[0].insert(i);
	
	// Maximum Cardinality Search
	while(i >= 0)
	{
		int v = *Set[j].begin();
		Set[j].erase(v);
		
		alpha[v] = i;
		size[v] = -1;

		fill(visitado.begin(), visitado.end(), false);
		for(auto u: simAdj[v])
		{
			int w = u.first;
			if(visitado[w])
				continue;

			if(size[w] < 0)
				continue;

			visitado[w] = true;
			Set[size[w]].erase(w);
			size[w]++;
			Set[size[w]].insert(w);
		}

		i--;
		j++;

		while(j > 0 && Set[j].empty())
			j--;
	}

	return alpha; 
}

vector<int> Chordal::coloring()
{
	vector<int> alpha = Chordal::perfectEliminationOrdering();
	vector<int> colors (n, 0);
	vector<int> vizinhanca;
	vector<bool> visitado (n, false);

	for(int i = 0; i < n; i++)
	{
		int cores = 0;
		vizinhanca.clear();
		fill(visitado.begin(), visitado.end(), false);
		
		for(auto u: simAdj[alpha[i]])
		{
			int w = u.first;
			if(visitado[w])
				continue;
			
			visitado[w] = true;
			vizinhanca.push_back(colors[w]);
			cores++;
		}

		vector<int> possiveis (cores, 0);
		for(auto c: vizinhanca)
			if(c <= cores)
			   possiveis[c-1]++;	
			
		for(int i = 0; i < cores; i++)
			if(possiveis[i] == 0)
			{
				colors[alpha[i]] = i+1;
				break;
			}
	}
}

int Chordal::chromaticNumber()
{
	vector<int> cores = Chordal::coloring();
	int maior = -1;
	for(auto c: cores)
		maior = (c > maior? c: maior);

	return maior;
}
